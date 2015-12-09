#include "db.hpp"
#include <fstream>
#include <functional>

namespace db {
//============================================================================
//
  auto from_string(const string_t& s) -> record_t {
    return from_string(s.size(), s.c_str());
  }
//============================================================================
//
  auto from_string(size_t len, const char* cstr) -> record_t {
    size_t idx = 0;
    string_t key;

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
    
    return record_t(key, string_t(cstr + value_start));
  }
//============================================================================
//
  auto to_string(const record_t& record) -> string_t {

    auto process_key = [] (const string_t& key) {     
      string_t line;
      const auto len = key.size();
      auto idx = len * 0;
      auto getch = [&] {
        return idx < len ? key[idx++] : 0;
      };

      std::function<string_t(void)> recurse = [&] {
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

auto from_file(const string_t& path) -> map_t {
  return from_file(path, nullptr);
}

auto from_file(const string_t& path, const map_t* defaults) -> map_t {
  using namespace std;
  ifstream file(path);

  // copy defaults if provided
  map_t db = defaults ? *defaults : map_t();

  string linebuf;
  while(true) {
    if(!getline(file, linebuf).good()) { break; }
    auto r = db::from_string(linebuf);
    db.erase(r.first);
    db.insert(r);
  }
  return db;
};

auto to_file(const string_t& path, const map_t& db) -> void {
  using namespace std;
  ofstream file(path);

  for(const auto& r : db) {
    file << db::to_string(r) << "\n";
  }
}

//============================================================================
}; // namespace db
