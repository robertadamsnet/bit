#ifndef FILE_HPP_20151211151922
#define FILE_HPP_20151211151922 

#include "resource.hpp"
#include <stdio.h>

namespace file {

  template<class...Args>
  auto make_file(Args&&...args) {
    auto ctor = [&] {
      return fopen(std::forward<Args>(args)...);
    };
    
    auto dtor = [&] (auto&& handle) {
      fclose(handle);
    };
    return make(ctor, dtor);
  };
  
}

#endif//FILE_HPP_20151211151922
