#ifndef DB_KEYS_HPP_20151211013427
#define DB_KEYS_HPP_20151211013427 

namespace db {
 
  constexpr auto key_sources() -> const char* { 
    return "@CPP-INPUT-SOURCES";
  };

  constexpr auto key_build_output_dir() -> const char* { 
    return "@CPP-OUTPUT-DIR"; 
  }

  constexpr auto key_bit_version() -> const char* { 
    return "@VERSION"; 
  }

  constexpr auto key_bit_cpp_compiler() -> const char* { 
    return "@BIT-CPP-COMPILER"; 
  }

  constexpr auto key_bit_cpp_flags() -> const char* { 
    return "@BIT-CPP-FLAGS"; 
  }


  constexpr auto key_bit_dirs_include() -> const char* { 
    return "@BIT-DIRS-INCLUDE"; 
  } 
  
  constexpr auto key_bit_dirs_link() -> const char* { 
    return "@BIT-DIRS-LINK"; 
  }


  constexpr auto key_project_dirs_source() -> const char* { 
    return "@PROJECT-DIRS-SOURCE";
  } 
  
  constexpr auto key_project_dirs_build() -> const char* { 
    return "@PROJECT-DIRS-BUILD"; 
  }

}; // namespace db

#endif//DB_KEYS_HPP_20151211013427

