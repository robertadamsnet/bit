 /* 
 * Copyright (C) 2015 by Robert T. Adams
 * All rights reserved.
 *
 * Licensed under the terms of the GNU General Public License, version 2.
 * See LICENSE.txt for complete license.
 *
 */
#include "db.hpp"
#include <fstream>
#include <functional>
namespace db {
//============================================================================
//
  auto from_string(const std::string& s) -> record_t {
    return from_string(s.size(), s.c_str());
  };

//============================================================================
//
  auto from_string(size_t len, const char* cstr) -> record_t {
    size_t idx = 0;
    std::string key;

    auto getch =[&] {
      return idx < len ? cstr[idx++] : 0;
    };

    std::function<void(void)> process_key = [&] {
      auto ch = getch();
      switch(ch) {
      // terminate on delimiter or null
      case  0:
      case ':':
        return;
      // process extra char when escaped with '\'
      case '\\':
        ch = getch();
        break;
      };
      key.append(1, ch);
      // recurse
      process_key();
    };

    process_key();

    auto value_start  = idx < len ? idx     : len;
    
    return record_t(key, std::string(cstr + value_start));
  }
//============================================================================
//
  auto to_string(const record_t& record) -> std::string {

    auto process_key = [] (const std::string& key) {     
      std::string line;
      const auto len = key.size();
      auto idx = len * 0;
      auto getch = [&] {
        return idx < len ? key[idx++] : 0;
      };

      std::function<std::string(void)> recurse = [&] {
        auto ch = getch();
        switch(ch) {
        case 0:
          return line;
        case ':':
        case '\\':
          line += '\\';      
        };
        line += ch;
        return recurse();
      };

      return recurse();
    };

    return process_key(record.first) + ":" + record.second;
  };

//============================================================================
//
auto from_file(const std::string& path) -> map_t {
  return from_file(path, nullptr);
}

auto from_file(const std::string& path, const map_t* defaults_db) -> map_t {
  using namespace std;
  ifstream file(path);

  map_t db = defaults_db ? *defaults_db : map_t();

  string linebuf;

  while(true) {
    if(!getline(file, linebuf).good()) { break; }
    auto r = db::from_string(linebuf);
    db.erase(r.first);
    db.insert(r);
  }
  return db;
};

auto to_file(const std::string& path, const map_t& db) -> void {
  using namespace std;
  ofstream file(path);

  for(const auto& r : db) {
    file << db::to_string(r) << "\n";
  }
}

//============================================================================
}; // namespace db
