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

#include "gtest/gtest.h"

#include "config.h"
#include "run_sc_bench.h"

namespace parasat {

static fs::path rand_root = fs::path(PARASAT_TEST_DATA_DIR) / "sc18_random";

class TestRndBarthel : public TestRunScBench {
public:
  void SetUp() {
    data_dir = rand_root / "cnf" / "rnd-barthel";
    InitReference("ref_sc18_barthel.json");
  }
}; // class TestRndBarthel

TEST_F(TestRndBarthel, fla_barthel_200_1) { Check("fla-barthel-200-1.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_2) { Check("fla-barthel-200-2.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_3) { Check("fla-barthel-200-3.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_4) { Check("fla-barthel-200-4.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_200_5) { Check("fla-barthel-200-5.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_220_1) { Check("fla-barthel-220-1.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_220_2) { Check("fla-barthel-220-2.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_220_3) { Check("fla-barthel-220-3.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_220_4) { Check("fla-barthel-220-4.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_220_5) { Check("fla-barthel-220-5.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_240_1) { Check("fla-barthel-240-1.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_240_2) { Check("fla-barthel-240-2.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_240_3) { Check("fla-barthel-240-3.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_240_4) { Check("fla-barthel-240-4.cnf"); }
TEST_F(TestRndBarthel, fla_barthel_240_5) { Check("fla-barthel-240-5.cnf"); }

class TestRndKomb : public TestRunScBench {
public:
  void SetUp() {
    data_dir = rand_root / "cnf" / "rnd-komb";
    InitReference("ref_sc18_komb.json");
  }
}; // class TestRndKomb

TEST_F(TestRndKomb, fla_komb_200_1) { Check("fla-komb-200-1.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_2) { Check("fla-komb-200-2.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_3) { Check("fla-komb-200-3.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_4) { Check("fla-komb-200-4.cnf"); }
TEST_F(TestRndKomb, fla_komb_200_5) { Check("fla-komb-200-5.cnf"); }
TEST_F(TestRndKomb, fla_komb_220_1) { Check("fla-komb-220-1.cnf"); }
TEST_F(TestRndKomb, fla_komb_220_2) { Check("fla-komb-220-2.cnf"); }
TEST_F(TestRndKomb, fla_komb_220_3) { Check("fla-komb-220-3.cnf"); }
TEST_F(TestRndKomb, fla_komb_220_4) { Check("fla-komb-220-4.cnf"); }
TEST_F(TestRndKomb, fla_komb_220_5) { Check("fla-komb-220-5.cnf"); }
TEST_F(TestRndKomb, fla_komb_240_1) { Check("fla-komb-240-1.cnf"); }
TEST_F(TestRndKomb, fla_komb_240_2) { Check("fla-komb-240-2.cnf"); }
TEST_F(TestRndKomb, fla_komb_240_3) { Check("fla-komb-240-3.cnf"); }
TEST_F(TestRndKomb, fla_komb_240_4) { Check("fla-komb-240-4.cnf"); }
TEST_F(TestRndKomb, fla_komb_240_5) { Check("fla-komb-240-5.cnf"); }

class TestRndQhid : public TestRunScBench {
public:
  void SetUp() {
    data_dir = rand_root / "cnf" / "rnd-qhid";
    InitReference("ref_sc18_qhid.json");
  }
}; // class TestRndQhid

TEST_F(TestRndQhid, fla_qhid_200_1) { Check("fla-qhid-200-1.cnf"); }
TEST_F(TestRndQhid, fla_qhid_200_2) { Check("fla-qhid-200-2.cnf"); }
TEST_F(TestRndQhid, fla_qhid_200_3) { Check("fla-qhid-200-3.cnf"); }
TEST_F(TestRndQhid, fla_qhid_200_4) { Check("fla-qhid-200-4.cnf"); }
TEST_F(TestRndQhid, fla_qhid_200_5) { Check("fla-qhid-200-5.cnf"); }
TEST_F(TestRndQhid, fla_qhid_220_1) { Check("fla-qhid-220-1.cnf"); }
TEST_F(TestRndQhid, fla_qhid_220_2) { Check("fla-qhid-220-2.cnf"); }
TEST_F(TestRndQhid, fla_qhid_220_3) { Check("fla-qhid-220-3.cnf"); }
TEST_F(TestRndQhid, fla_qhid_220_4) { Check("fla-qhid-220-4.cnf"); }
TEST_F(TestRndQhid, fla_qhid_220_5) { Check("fla-qhid-220-5.cnf"); }
TEST_F(TestRndQhid, fla_qhid_240_1) { Check("fla-qhid-240-1.cnf"); }
TEST_F(TestRndQhid, fla_qhid_240_2) { Check("fla-qhid-240-2.cnf"); }
TEST_F(TestRndQhid, fla_qhid_240_3) { Check("fla-qhid-240-3.cnf"); }
TEST_F(TestRndQhid, fla_qhid_240_4) { Check("fla-qhid-240-4.cnf"); }
TEST_F(TestRndQhid, fla_qhid_240_5) { Check("fla-qhid-240-5.cnf"); }

}; // namespace parasat
