STYLE GUIDE         {#styleguide}
===========

-# C++14

    * This software uses the C++14 standard library.  You should use clang++ or
      gcc or any other compiler which is compliant with this standard.  Maybe
      even the newer versions of Visual C++.

-# Namespaces

    * All code should be placed into namespaces according to functionality.
      For instance, a group of functions which process command-line options
      might be placed in the 'opt' namespace.

    * Private global data should be placed in anonymous namespaces, in the cpp
      file rather than the header.

-# Types

    * Type names are lowercase, and are suffixed with "_t".  If this would
      cause a name clash, use "_type" instead.

    * Wherever possible and practical, use factory functions to create objects.
      This way you can use the following syntax:

          auto some_object = some_object_factory(constructor, arguments);

      The goal is to avoid hard-coding types into the program logic.

-# Functions and lambdas

    * Avoid gargantuan monolithic functions.  Split them up.

-# Function arguments and return types.

    * "Pass-by" conventions:

      Type                                    | Pass-by
      ----------------------------------------|------------------
      Built-in (e.g. int, float)              | value
      Complex  (classes and structs)          | const reference
      Arguments to constructors and factories | value
        
    * Return type conventions:

      Type of function                        | Return as
      ----------------------------------------|------------------
      Factory functions                       | value
      Polymorphic factory functions           | rvalue reference
      Pass-through (un-owned by function)     | const lvalue reference
      Returning built-in types                | value

-# Default function arguments

    * As this software makes liberal use of lambda functions and other function
      objects, default function arguments should be avoided.  Override them
      instead to prevent problems with typing.

-# Classes

    * Classes should be avoided, unless you *need* to create an variable that
      has object-like behavior.  

    * If classes *must* be used, define objects which are immutable and adhere
      to [SOLID](https://en.wikipedia.org/wiki/SOLID_%28object-oriented_design%29)
      design principles.  

    * Classes may also be used to group static functions conceptually, but
      namespaces are usually a better choice for this.

-# Tuples

    * Tuples should be accompanied by a convenience enum which names its elements.
    * Example:
  

          using record_t = tuple<int, string, int>            // <- Huh?

          enum { record_id, record_name, record_spouse_id };  // <- Oh, okay.
          
          record_t r(123, "Joseph Smith", 467);

          auto id         = get<record_id>(r);

          auto name       = get<record_name>(r);

          auto spouse_id  = get<record_spouse_id>(r);

-# Enums

    * As long as you don't abuse them, use the old C-style enums and wrap them
      in a namespace or struct if you're avoiding scope pollution.
    * Treat enums as named constants of integer type.
    * When comparing, use `int == enum`, not `enum == int`.
      * Remember: enums are convertible to int, not the other way around.  Why?
        Because an int can hold all possible enum values, but an enum has a
        finite set of values.

-# Doxygen

    * All doxygen tags should be placed in **headers only**.  
    * Every program element should be documented with at least a  tag.
    * All function arguments, class/struct members, enum members, etc, should be documented inline; this prevents unnecessary code duplication in the comments.
      Each member should occupy its own line.  For example:


      auto some_func(
        int arg1;       //!< Arg1 is an int...nuff said.
        float arg2;     //!< Arg2 is not an int.  
      ) -> string_t;    //!< Return value is a string;


-# Text alignment

    * Try to line up declarations, definitions, and initializations per group.

    * Example:


          // group of variables aligned together
          auto apples         = 1;
          auto oranges        = 2;
          auto energy         = (m * c) * (m * c);

          // group of type aliases aligned together
          using a_long_name_for_a_type_t    = int;
          using a_shorter_type_name_t       = string_t;

          // group of functions
          auto some_func()        -> int;
          auto another_func()     -> float;
        
-# Indentation / Braces

    * Braces are on the same line as the function signature **unless** it spans
      more than one line.

    * Try to put a semicolon behind every curly brace.  The compiler won't
      complain if you don't need it, but you can avoid re-compiles when you
      change functions to lambdas or namespaces to classes.

    * Examples:


        int foo() {
        };              // <- Don't need the semicolon, but it won't kill you.
        
        int a_pretty_long_function_with_a_lot_of_args(int arg1, int arg2, 
          int arg3)     // <- Indented continuation.
        {               // <- Newline for readability.
        };

        class SomeClass {         // <- Same line.
        public:                   // <- Flush to class name.
          SomeClass();
          ~SomeClass();

          // Inline public interfaces which only call pure virtuals:
          auto some_capability() { return v_some_capability(); }

        private:
          int a_member_;          // <- Add trailing underscore to 
          int another_member_;    //    private members

          virtual auto v_some_capability() -> int = 0;
        };

        SomeClass::SomeClass()    
          : a_member_(),          // <- Initializer on separate, indented line
            another_member_()     // <- Member-per-line is optional
        {                         // <- Newline for opening brace.
          foo();
        };
