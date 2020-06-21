// =============================================================================
// MIT License
//
// Copyright (c) 2020 Princeton University
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// =============================================================================

#include <filesystem>
#include <string>
#include <vector>

#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/flags/usage.h>
#include <fmt/format.h>
#include <lyra/lyra.hpp>
#include <taskflow/taskflow.hpp>

#include <parasat/core/Dimacs.h>
#include <parasat/core/Solver.h>
#include <parasat/utils/Logging.h>
#include <parasat/utils/System.h>

using namespace parasat;
namespace fs = std::filesystem;

static Solver* solver;

static void SIGINT_interrupt(int) { solver->interrupt(); }

static void SIGINT_exit(int) {
  PSAT_LOG << "*** INTERRUPTED ***";
  if (solver->verbosity > 0) {
    solver->printStats();
  }
  PSAT_LOG << "*** INTERRUPTED ***";
  _exit(1);
}

ABSL_FLAG(uint32_t, jobs, 4, "Number of parallel jobs");

int main(int argc, char** argv) {
  SetToStdErr(true);

  // cli setup
  bool show_help_msg = false;
  std::string input_file = "data/foo.cnf";

  auto cli = lyra::help(show_help_msg) | // default option
             lyra::arg(input_file, "input")("input cnf file");

  auto result = cli.parse({argc, argv});
  // ignore check to allow flags
  // PSAT_CHECK(result) << result.errorMessage();

  if (show_help_msg) {
    PSAT_LOG << cli;
    return 0;
  }

  PSAT_CHECK(fs::is_regular_file(input_file));

  // enable flags
  absl::SetProgramUsageMessage("MiniSAT-based Parallel SAT solver");
  absl::ParseCommandLine(argc, argv);

  // get flags
  auto job_num = absl::GetFlag(FLAGS_jobs);

  // ****** testing taskflow ******
  std::vector<Solver*> solvers;
  for (auto i = 0; i < job_num; i++) {
    auto s_ptr = new Solver();
    solvers.push_back(s_ptr);
  }

  for (auto s_ptr : solvers) {
    gzFile in = gzopen(input_file.c_str(), "rb");
    parse_DIMACS(in, *s_ptr, false);
    gzclose(in);
  }

  tf::Taskflow taskflow;

  auto exe_solve = [&](auto job_id) {
    PSAT_LOG << "Start task " << job_id;
    int ret_code = 0;
    vec<Lit> dummy;
    try {
      auto ret = solvers[job_id]->solveLimited(dummy);
      ret_code = ((ret == l_True) ? 10 : (ret == l_False) ? 20 : 0);
    } catch (OutOfMemoryException&) {
      ret_code = 0;
    }
    PSAT_LOG << fmt::format("Task {} result: {}", job_id, ret_code);
  };

  for (auto i = 0; i < job_num; i++) {
    auto exe_solve_wrap = [=]() { exe_solve(i); };
    auto task_i = taskflow.emplace(exe_solve_wrap);
  }

  tf::Executor executor;
  executor.run(taskflow).wait();

  for (auto i = 0; i < job_num; i++) {
    delete solvers[i];
  }
  // ****** end testing taskflow ******

  // initiate the solver
  Solver s;
  solver = &s;

  // use signal handlers that forcibly quit until the solver will be able to
  // respond to interrupts:
  sigTerm(SIGINT_exit);

  // parse the input file
  gzFile in = gzopen(input_file.c_str(), "rb");
  parse_DIMACS(in, s, false);
  gzclose(in);

  // change to signal-handlers that will only notify the solver and allow it to
  // terminate voluntarily:
  sigTerm(SIGINT_interrupt);

  if (!s.simplify()) {
    PSAT_LOG << "unsat (solved by unit propagation)";
    return 0;
  }

  // solve
  int ret_code = 0;

  vec<Lit> dummy;
  try {
    auto ret = s.solveLimited(dummy);
    ret_code = ((ret == l_True) ? 10 : (ret == l_False) ? 20 : 0);
  } catch (OutOfMemoryException&) {
    ret_code = 0;
  }

  PSAT_LOG << ((ret_code == 10) ? "sat"
                                : (ret_code == 20) ? "unsat" : "unknown");

  return ret_code;
}
