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

static fs::path main_root = fs::path(PARASAT_TEST_DATA_DIR) / "sc18_main";

class DISABLED_TestMainCril : public TestRunScBench {
public:
  void SetUp() {
    data_dir = main_root / "final" / "CRIL";
    InitReference("ref_sc18_cril.json");
  }
}; // class TestMainCril

TEST_F(DISABLED_TestMainCril, t103_2_0) { Check("T103.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t105_2_0) { Check("T105.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t107_2_0) { Check("T107.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t116_2_0) { Check("T116.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t117_2_0) { Check("T117.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t122_2_0) { Check("T122.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t125_2_0) { Check("T125.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t129_2_0) { Check("T129.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t56_2_0) { Check("T56.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t62_2_0) { Check("T62.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t77_2_0) { Check("T77.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t82_2_0) { Check("T82.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t84_2_0) { Check("T84.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t86_2_0) { Check("T86.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t87_2_0) { Check("T87.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t90_2_0) { Check("T90.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t92_2_0) { Check("T92.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t93_2_0) { Check("T93.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t96_2_0) { Check("T96.2.0.cnf"); }
TEST_F(DISABLED_TestMainCril, t98_2_0) { Check("T98.2.0.cnf"); }

}; // namespace parasat

