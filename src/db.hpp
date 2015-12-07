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


  auto record_from_string(size_t, const char*)        -> record_t;
  auto record_from_string(const string_t&)            -> record_t;
  auto string_from_record(const record_t&)              -> string_t;

}; // namespace db
//============================================================================
//
#endif//DB_HPP_2015_1206_124034
