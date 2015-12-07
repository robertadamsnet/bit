#ifndef BIT_ENV_HPP_2015_1205_123113
#define BIT_ENV_HPP_2015_1205_123113 

#include <string>
#include <boost/lexical_cast.hpp>

using string = std::string;

template<class T>
auto cat(T&& arg) -> auto {
  return boost::lexical_cast<string>(arg);
}

template<class T, class...Args>
auto cat(T&& arg1, Args...args) -> auto {
  return cat(arg1) + cat(args...);
}

inline
auto bit_dir() -> auto {
  static string bit_dir_= ".bit";
  return bit_dir_.c_str();
}

inline
auto bit_db() -> auto {
  static string bit_db_ = cat(bit_dir(), "/db.csv");
  return bit_db_.c_str();
}


#endif//BIT_ENV_HPP_2015_1205_123113
