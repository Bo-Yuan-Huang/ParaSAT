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

#include <parasat/utils/Logging.h>

namespace parasat {

void SetLogLevel(const int& lvl) { FLAGS_minloglevel = lvl; }

void SetLogPath(const std::string& path) { FLAGS_log_dir = path; }

void SetToStdErr(const int& to_err) { FLAGS_logtostderr = to_err; }

// DebugLog
LogInitter::LogInitter() {
  google::InitGoogleLogging("psat");
  FLAGS_minloglevel = 0; // log all message above level 0
#ifndef NDEBUG
  FLAGS_logtostderr = 1; // log INFO and WARNING to stderr
#else                    // NDEBUG
  FLAGS_logtostderr = 0; // not logging INFO and WARNING to stderr
#endif                   // NDEBUG
}

std::set<std::string> DebugLog::debug_tags_;

LogInitter DebugLog::init_;

void DebugLog::Enable(const std::string& tag) { debug_tags_.insert(tag); }

void DebugLog::Disable(const std::string& tag) { debug_tags_.erase(tag); }

void DebugLog::Clear() { debug_tags_.clear(); }

bool DebugLog::Find(const std::string& tag) {
  return (debug_tags_.find(tag) != debug_tags_.end());
}

}; // namespace parasat
