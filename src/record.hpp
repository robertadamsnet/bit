#ifndef RECORD_HPP_2015_1207_131423
#define RECORD_HPP_2015_1207_131423 

#include <string>
#include <map>
#include <fstream>

namespace record {
//============================================================================
//

  using string_t        = std::string;
  using record_t        = std::pair<string_t, string_t>;
  using map_t           = std::map<string_t, string_t>;


  auto from_string(size_t, const char*)        -> record_t;
  auto from_string(const string_t&)            -> record_t;
  auto to_string(const record_t&)              -> string_t;

}; // namespace record
//============================================================================
//

#endif//RECORD_HPP_2015_1207_131423
