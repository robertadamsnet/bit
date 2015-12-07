#ifndef DB_HPP_2015_1206_124034
#define DB_HPP_2015_1206_124034 

#include <string>
#include <map>
#include <fstream>



namespace db {
//============================================================================
//

  using string_t        = std::string;
  using record_t        = std::pair<string_t, string_t>;
  using map_t           = std::map<string_t, string_t>;

  auto get_cwd() -> string_t;

  auto get_record(const char* buffer, const size_t size) -> record_t;
  auto get_record(const string_t& str) -> record_t;

  auto init_defaults() -> map_t;

  auto open_db() -> bool;

}; // namespace db
//============================================================================
//
#endif//DB_HPP_2015_1206_124034
