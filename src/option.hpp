/* Copyright (C) 2015 by Robert T. Adams
 * All rights reserved.
 *
 * Licensed under the terms of the GNU General Public License, version 2.
 * See LICENSE.txt for more information.
 *
 */

#ifndef OPTIONS_HPP_2015_1203_225632
#define OPTIONS_HPP_2015_1203_225632 

#include <functional>
#include <tuple>
#include <list>

//! \brief Option processing.
namespace opt {
//============================================================================
//! \brief Option argument availability.
//!  
//! These constants are passed via the option_t tuple to specify whether the
//! option requires an argument.
enum {
  arg_none,                           //!< No argument required. 
  arg_required,                       //!< Argument required.
  arg_optional                        //!< Argument optional.
};

using string_t      = std::string;    //!< Type for strings used in this module.
using action_t      = std::function<int(const string_t&)>;
                                      //!< Option "handler" type.

//! \brief Option record. 
//!   Tuples of this type describe a single valid option that can be supplied
//!   via the command line.
using option_t      = std::tuple<char, const char*, const char*, int, action_t>;

//! \brief Field accessor constants for the option_t tuple.
enum {
  opt_short,                          //!< Short option (char).
  opt_long,                           //!< Long option (string).
  opt_help,                           //!< Help text (string).
  opt_arg,                            //!< Argument mode (enum Arg).
  opt_action                          //!< Option handler (function).
};

using option_list_t = std::list<option_t>;
                                      //!< List of options to be passed to
                                      //!< parse function.

/*! \brief  Parse command line options.
 *  \return Code from the first handler to produce an error; should be
 *          returned from main().
 *  \example opt-parse.cpp
 */
auto parse(
    const option_list_t& opts,      //!< List of options this program can 
                                    //!< handle.
    const action_t& non_opt_action, //!< Handler for non-option arguments.
    int argc,                       //!< Argument count from main().
    char* argv[]                    //!< Argument array from main().
  ) -> int;                         

//============================================================================
}; // namespace opt

#endif//OPTIONS_HPP_2015_1203_225632
