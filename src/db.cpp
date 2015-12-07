#include "db.hpp"

#include <unistd.h>
#include <stdlib.h>

namespace db {
//============================================================================
//
auto get_cwd() -> string_t {
  auto cwd_cstr = get_current_dir_name();
  string_t cwd(cwd_cstr);
  free(cwd_cstr);
  return cwd;
};

//============================================================================
//
auto init_defaults() -> map_t {
  map_t map;
  
  string_t cwd = get_cwd();

  map["BIT_ROOT"]                 = cwd + "/.bit";
  map["BIT_DB_NAME"]              = map["BIT_ROOT"] + "/db.csv";

  return map;
};

//============================================================================
//
auto open_db() -> std::FILE* {
  auto handle = fopen(   
};

//============================================================================
//

auto get_record(const char* buffer, const size_t size) -> record_t {
  size_t index = 0;
  
  auto getch = [&] {
    return index < size ? buffer[index++] : 0;
  };

  auto find_delim = [&] {
    while(index < size) {
      switch(getch()) {
      case 0:
      case ':':
        return index;
      case '\\':
        getch();
      }
    }
    return index;
  };

  auto delim          = find_delim();
  auto key_end        = delim > 0    ? delim - 1 : 0;
  auto value_begin    = delim < size ? delim     : size;

  string_t key(buffer, key_end);
  string_t value(buffer + value_begin);

  return make_pair(key, value);
};

//============================================================================
//

auto get_record(const string_t& str) -> record_t {
  return get_record(str.c_str(), str.size());
}

//============================================================================
} // namespace db
