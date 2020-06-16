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
#include <fstream>

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

class TestSat19Rand : public ::testing::Test {
public:
  TestSat19Rand() {}
  ~TestSat19Rand() {}

  void SetUp() {}
  void TearDown() {}

  fs::path rand_root = fs::path(PARASAT_TEST_DATA_DIR) / "sat19_rand";
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

}; // class TestSat19Rand

class TestRndBarthel : public TestSat19Rand {
public:
  void SetUp() {
    InitReference("ref_rnd_barthel.json");
    data_dir = rand_root / "cnf" / "rnd-barthel";
  }
}; // class TestRndBarthel

TEST_F(TestRndBarthel, fla_barthel_200_1) { Check("fla-barthel-200-1.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_2) { Check("fla-barthel-200-2.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_3) { Check("fla-barthel-200-3.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_4) { Check("fla-barthel-200-4.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_5) { Check("fla-barthel-200-5.cnf"); }

class TestRndKomb : public TestSat19Rand {
public:
  void SetUp() {
    InitReference("ref_rnd_komb.json");
    data_dir = rand_root / "cnf" / "rnd-komb";
  }
}; // class TestRndKomb

TEST_F(TestRndKomb, fla_komb_200_1) { Check("fla-komb-200-1.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_2) { Check("fla-komb-200-2.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_3) { Check("fla-komb-200-3.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_4) { Check("fla-komb-200-4.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_5) { Check("fla-komb-200-5.cnf"); }

}; // namespace parasat
