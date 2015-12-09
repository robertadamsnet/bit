#ifndef DB_HPP_20151207132454
#define DB_HPP_20151207132454 

#include <string>
#include <map>

namespace db {
//============================================================================
//
  using string_t        = std::string;

  //! \brief Use 'record_t' objects to store key/value records in the database.
  using record_t        = std::pair<string_t, string_t>;
  //! \brief Parse a c-string into a key/value pair.
  auto from_string(size_t, const char*)        -> record_t;
  //! \brief Parse a std::string into a key/value pair.
  auto from_string(const string_t&)            -> record_t;
  //! \brief Convert a key/value pair into a string.
  auto to_string(const record_t&)              -> string_t;

//============================================================================
//
  using map_t           = std::multimap<string_t, string_t>;

  //! \brief Process an entire text file into a multimap of key/value pairs.
  auto from_file(const string_t&) -> map_t;
  //! \brief Copy a multi-map of predefined records, then load the records
  //! from a text file.
  auto from_file(const string_t&, const map_t* defaults) -> map_t;
  //! \brief Convert a multi-map of records back into a text file.
  auto to_file(const string_t&, const map_t&) -> void;

//============================================================================
}; // namespace db
#endif//DB_HPP_20151207132454
