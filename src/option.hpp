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
#include "types.hpp"

#include <functional>
#include <tuple>
#include <list>


//! \brief Option processing.
namespace opt {
//============================================================================
//! \brief Option argument availability.
//!  
//! These constants are passed via the item_t tuple to specify whether the
//! option requires an argument.
enum {
  arg_none,                           //!< No argument required. 
  arg_required,                       //!< Argument required.
  arg_optional                        //!< Argument optional.
};

using string_t      = types::string_t;//!< Type for strings used in this module.
using action_t      = std::function<int(const string_t&)>;
                                      //!< Option "handler" type.
using default_t     = std::function<int(void)>;
//! \brief Option record. 
//!   Tuples of this type describe a single valid option that can be supplied
//!   via the command line.
using item_t      = std::tuple<char, const char*, const char*, int, action_t>;

//! \brief Factory function to create an option record.
//    Creates an option record.  Using a factory function allows use of auto
//    for type deduction--in case we want to change the option record type
//    in the future without having to re-write the world.  I also feel it's
//    easier to understand compiler errors in the context of a bad function
//    call, instead of an incorrect type error that is gushing with
//    templated code.
auto make(char, const char*, const char*, int, action_t) -> item_t;

//! \brief Field accessor constants for the item_t tuple.
enum {
  opt_short,                          //!< Short option (char).
  opt_long,                           //!< Long option (string).
  opt_help,                           //!< Help text (string).
  opt_arg,                            //!< Argument mode (enum Arg).
  opt_action                          //!< Option handler (function).
};

using list_t = std::list<item_t>;
                                      //!< List of options to be passed to
                                      //!< parse function.

template<class...Args>
auto make_list(Args&&...args) {
  list_t opts = { std::forward<Args>(args)... };
  return opts;
};

inline
auto make(char s, const char* l, const char* h, int has_arg, action_t a)
  -> item_t
{
  return make_tuple(s, l, h, has_arg, a);
}
//! \brief  Parse command line options.
/*!
    \return The error code returned from the first handler to terminate with an
            error.  
*/
auto parse(
    const list_t& opts,             //!< List of options this program can 
                                    //!< handle.
    const action_t& non_opt_action, //!< Handler for non-option arguments.
    const default_t& default_action //!< Handler if no options are given.
  ) -> std::function<int(int,char*[])>;                         


//!  \example opt-parse.cpp

//============================================================================
}; // namespace opt

#endif//OPTIONS_HPP_2015_1203_225632
