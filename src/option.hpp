#ifndef OPTIONS_HPP_2015_1203_225632
#define OPTIONS_HPP_2015_1203_225632 
/* 
 * Copyright (C) 2015 by Robert T. Adams
 * All rights reserved.
 *
 * Licensed under the terms of the GNU General Public License, version 2.
 * See LICENSE.txt for complete license.
 *
 */

#include <string>
#include <functional>
#include <vector>

namespace option {
  using std::string;

  enum {
    is_short,
    is_long,
    is_value
  };

  using array_t = std::vector<string>;

  using option_t            = std::string;
  using callback_t          = std::function<void(const option_t&)>;
  using array_t         = std::vector<string>;
  using array_callback_t    = std::function<void(const array_t&)>;

  void get_long_opt(const string& opt, const callback_t& callback);
  void get_short_opts(const string& opt, const callback_t& callback);
  void parse(int argc, char* argv[], const callback_t& cb);
  void parse(int argc, char* argv[], const array_callback_t& cb);

  auto parse(int argc, char* argv[]) -> array_t;

  auto is_value_delimiter(char c) -> bool;
};// namespace option

inline
auto option::is_value_delimiter(char c) -> bool {
  switch(c) {
  case '=':
  case ':':
    return true;
  default:
    return false;
  };
}

inline
void option::get_long_opt(const string& opt, const callback_t& callback) 
{
  for(int idx = 0; idx < opt.size(); ++idx) {
    auto c = opt[idx];
    if(is_value_delimiter(c)) {
      string opt_str = std::string(opt, 0, idx);
      callback(opt_str);
      string nonopt_str = std::string(opt, idx);
      callback(nonopt_str);
      return;
    }
  };
  callback(opt);
}

inline
void option::get_short_opts(const string& opt, const callback_t& callback)
{
  auto sz = opt.size();
  static const string dash("-");

  for(int i = 1; i < sz; ++i) {
    auto shortopt = dash + opt[i];
    callback(shortopt);
  }
}

inline
void option::parse(int argc, char* argv[], const callback_t& callback)
{
  for(int i = 1; i < argc; ++i) {
    const std::string opt = argv[i];
    // if the argument begins with '-', it could be a bunch of short opts
    // strung together
    if(opt[0] == '-') {
      if(opt[1] == '-') {
        get_long_opt(opt, callback);
      }
      else {
        get_short_opts(opt, callback);
      }
    } 
    else {
      callback(opt);
    }
  }
}

inline
void option::parse(int argc, char* argv[], const array_callback_t& callback) 
{
  auto opts = parse(argc, argv);
  callback(opts);
}

inline
auto option::parse(int argc, char* argv[]) -> array_t 
{
  array_t opts;

  parse(argc, argv, [&] (const std::string& s) {
      opts.push_back(s);
    });

  return opts;
};

#endif//OPTIONS_HPP_2015_1203_225632
