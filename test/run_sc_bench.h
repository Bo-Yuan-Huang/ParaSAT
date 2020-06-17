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

#ifndef TEST_RUN_SC_BENCH_H__
#define TEST_RUN_SC_BENCH_H__

#include <filesystem>
#include <fstream>

#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <parasat/core/Dimacs.h>
#include <parasat/core/Solver.h>
#include <parasat/utils/Logging.h>

#include "gtest/gtest.h"

#include "config.h"

namespace parasat {

namespace fs = std::filesystem;
using json = nlohmann::json;

static decltype(json::object()) reference;
static fs::path current_ref_file;

class TestRunScBench : public ::testing::Test {
public:
  TestRunScBench() {}
  ~TestRunScBench() {}

  void SetUp() {}
  void TearDown() {}

  // fs::path rand_root;
  fs::path data_dir;

  int Solve(const fs::path& file) {
    Solver s;

    gzFile in = gzopen(file.c_str(), "rb");
    parse_DIMACS(in, s, false);
    gzclose(in);

    int st = 0;
    vec<Lit> dummy;
    try {
      auto ret = s.solveLimited(dummy);
      st = (ret == l_True) ? 10 : (ret == l_False) ? 20 : 0;
    } catch (OutOfMemoryException&) {
      st = 0;
    }
    return st;
  }

  void Check(const std::string& file) {
    auto input_file = data_dir / file;
    if (fs::is_regular_file(input_file)) {
      // solve result
      auto ret = Solve(input_file);
      // reference result
      auto ref = reference.at(file).get<int>();
      // compare
      EXPECT_EQ(ref, ret);
    } else {
      PSAT_ERROR << fmt::format("No file named {} found", input_file.string());
    }
  }

  void InitReference(const std::string& file) {
    auto ref_file = fs::path(PARASAT_TEST_DATA_DIR) / file;

    // avoid repeatly reading reference file
    if (ref_file == current_ref_file) {
      return;
    }
    current_ref_file = ref_file;

    // parse the reference
    if (fs::is_regular_file(ref_file)) {
      std::ifstream fin(ref_file);
      if (fin.is_open()) {
        fin >> reference;
        fin.close();
      }
    }
  }

}; // class TestRunScBench

}; // namespace parasat

#endif // TEST_RUN_SC_BENCH_H__
