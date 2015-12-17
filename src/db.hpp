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

#include "types.hpp"

#include <string>
#include <map>
#include <functional>

//! \brief Database functions.
namespace db {
  namespace control {

  }; // namespace control
//============================================================================
//
  //! \brief List of sources to compile.
  constexpr auto key_sources() -> const char* { 
    return "@CPP-INPUT-SOURCES";
  };
  //! \brief Software version.
  constexpr auto key_bit_version() -> const char* { 
    return "@VERSION"; 
  }
  //! \brief C++ compiler executable.
  constexpr auto key_bit_cpp_compiler() -> const char* { 
    return "@BIT-CPP-COMPILER"; 
  }
  //! \brief C++ compiler flags.
  constexpr auto key_bit_cpp_flags() -> const char* { 
    return "@BIT-CPP-FLAGS"; 
  }
  //! \brief List of include directories.
  constexpr auto key_bit_dirs_include() -> const char* { 
    return "@BIT-DIRS-INCLUDE"; 
  } 
  //! \brief List of link directories.
  constexpr auto key_bit_dirs_link() -> const char* { 
    return "@BIT-DIRS-LINK"; 
  }
  //! \brief Where to find the sources (input).
  constexpr auto key_project_dirs_input() -> const char* { 
    return "@PROJECT-DIRS-SOURCE";
  } 
  //! \brief Where to put the binaries (output.)
  constexpr auto key_project_dirs_output() -> const char* { 
    return "@PROJECT-DIRS-BUILD"; 
  }

  //! \brief String type used by this module.
  using string_t        = types::string_t;

  namespace config {
    inline
    auto dir() -> string_t { return ".bit"; };

    inline
    auto path() { return dir() + "/db"; };

  } // namespace config

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
  //! \brief Map type used by this module.
  using map_t           = std::map<string_t, string_t>;

  //! \brief Process the database from the default path.
  auto from_file() -> map_t;

  //! \brief Process an entire text file into a map of key/value pairs.
  auto from_file(
      const string_t& filename    //!< Name of the database file to open.
    ) -> map_t;                   //!< The map containing the key/value pairs 
                                  //!< that make up the database
  //! \brief Process an entire text file into a map of key/value pairs.
  auto from_file(
      const string_t& filename,   //!< Name of the database file to open.
      const map_t* defaults_db    //!< Pointer to existing map with defaults.
    ) -> map_t;                   //!< The map containing the key/value pairs 
                                  //!< that make up the database
  
  //! \brief Convert a map of records back into a text file.
  auto to_file(const string_t&, const map_t&) -> void;

  //! \brief Initialize a default database map.
  auto init_defaults() -> map_t;
//============================================================================
}; // namespace db
#endif//DB_HPP_20151207132454
