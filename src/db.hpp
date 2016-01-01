#ifndef DB_HPP_20151207132454
#define DB_HPP_20151207132454 
/* 
 * Copyright (C) 2015 by Robert T. Adams
 * All rights reserved.
 *
 * Licensed under the terms of the GNU General Public License, version 2.
 * See LICENSE.txt for complete license.
 *
 */

#include <string>
#include <map>
#include <functional>

//! \brief Database functions.
namespace db {
  //! \brief Use 'record_t' objects to store key/value records in the database.
  using record_t        = std::pair<std::string, std::string>;

  //! \brief Parse a c-string into a key/value pair.
  auto from_string(size_t, const char*)        -> record_t;

  //! \brief Parse a std::string into a key/value pair.
  auto from_string(const std::string&)            -> record_t;

  //! \brief Convert a key/value pair into a string.
  auto to_string(const record_t&)              -> std::string;

//============================================================================
//
  //! \brief Map type used by this module.
  using map_t           = std::map<std::string, std::string>;

  //! \brief Process the database from the default path.
  auto from_file() -> map_t;

  //! \brief Process an entire text file into a map of key/value pairs.
  auto from_file(
      const std::string& filename    //!< Name of the database file to open.
    ) -> map_t;                   //!< The map containing the key/value pairs 
                                  //!< that make up the database
  //! \brief Process an entire text file into a map of key/value pairs.
  auto from_file(
      const std::string& filename,   //!< Name of the database file to open.
      const map_t* defaults_db    //!< Pointer to existing map with defaults.
    ) -> map_t;                   //!< The map containing the key/value pairs 
                                  //!< that make up the database
  
  //! \brief Convert a map of records back into a text file.
  auto to_file(const std::string&, const map_t&) -> void;

//============================================================================
}; // namespace db
#endif//DB_HPP_20151207132454
