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

#ifndef PARASAT_UTILS_LOGGING_H__
#define PARASAT_UTILS_LOGGING_H__

#include <set>

#include <glog/logging.h>

namespace parasat {

/// Log debug message to INFO if the "tag" has been enabled.
#define PSAT_DLOG(tag) DLOG_IF(INFO, DebugLog::Find(tag)) << "[" << tag << "] "

/// Log the message to INFO (lvl 0). (Release)
#define PSAT_LOG LOG(INFO)

/// Log the message to INFO (lvl 0). (Debug)
#define PSAT_INFO DLOG(INFO)
/// Log the message to WARNING (lvl 1). (Debug)
#define PSAT_WARN DLOG(WARNING)
/// Log the message to ERROR (lvl 2). (Debug)
#define PSAT_ERROR DLOG(ERROR)
/// Conditionally log the message to INFO (lvl 0). (Debug)
#define PSAT_INFO_IF(b) DLOG_IF(INFO, b)
/// Conditionally log the message to WARNING (lvl 1). (Debug)
#define PSAT_WARN_IF(b) DLOG_IF(WARNING, b)
/// Conditionally log the message to ERROR (lvl 2). (Debug)
#define PSAT_ERROR_IF(b) DLOG_IF(ERROR, b)

/// Assertion with message logged to FATAL (lvl 3). (Debug)
#define PSAT_ASSERT(b) DLOG_IF(FATAL, !(b))

// Both in Debug and Release mode
// (Use only if high-assurance & non-performance critical)
/******************************************************************************/
/// Assertion with message logged to FATAL (lvl 3). (Debug/Release)
#define PSAT_CHECK(b) CHECK(b)
/// Assert equal with message logged to FATAL (lvl 3). (Debug/Release)
#define PSAT_CHECK_EQ(a, b) CHECK_EQ(a, b)
/// Assert not equal with message logged to FATAL (lvl 3). (Debug/Release)
#define PSAT_CHECK_NE(a, b) CHECK_NE(a, b)
/// Assert string equal with message logged to FATAL (lvl 3). (Debug/Release)
#define PSAT_CHECK_STREQ(a, b) CHECK_STREQ(a, b)
/// Assert point not NULL -- FATAL (lvl 3). (Debug/Release)
#define PSAT_NOT_NULL(ptr) CHECK_NOTNULL(ptr)

/// \brief Set the minimun log level.
/// Log messages at or above this level will be logged. (Default: 0)
/// - INFO: level 0
/// - WARNING: level 1
/// - ERROR: level 2
/// - FATAL: level 3
void SetLogLevel(const int& lvl);

/// \brief Set the path for log file.
/// If specified, logfiles are written into this directory instead of the
/// default logging directory (/tmp).
void SetLogPath(const std::string& path);

/// \brief Pipe log to stderr.
/// Log messages to stderr instead of logfiles, if set to 1.
void SetToStdErr(const int& to_err);

// Wrapper for debug tag log system.
/******************************************************************************/
/// A one-time class for initializing GLog.
class LogInitter {
public:
  /// Constructor to initialize GLog.
  LogInitter();
}; // class LogInitter

/// The wrapper for enabling and disabling debug tags.
class DebugLog {
public:
  /// Add a debug tag.
  static void Enable(const std::string& tag);

  /// Remove a debug tag.
  static void Disable(const std::string& tag);

  /// Clear all tags.
  static void Clear();

  /// Find if the tag is enabled.
  static bool Find(const std::string& tag);

private:
  /// The set of debug tags.
  static std::set<std::string> debug_tags_;

  /// The one and only initializer for the log system.
  static LogInitter init_;

}; // class DebugLog

}; // namespace parasat

#endif
