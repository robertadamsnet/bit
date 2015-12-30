#include "cmd-init.hpp"

#include <options/options.hpp>
#include <boost/filesystem.hpp>

void init_default() {
  init_create_bit_dir();
};

void init_create_bit_dir() {
  using namespace boost::filesystem;
  if(create_directory(".bit") == false) {
    std::string msg = "Could not create directory: ";
    msg += ".bit";
    throw std::runtime_error(msg);
  }  
};

void init_reset() {
  init_remove();
};

void init_remove()  {
  try {
    boost::filesystem::remove_all(".bit");
  } catch (...) {
    std::string msg = "Could not remove folder: ";
    msg += ".bit";
    throw std::runtime_error(msg);
  }
};


auto init_opt_table() -> void* {
  using namespace option;

  struct {

  } info;


  action_t do_remove        = [] (const std::string&) { init_remove(); };
  action_t do_reset         = [] (const std::string&) { init_reset(); };
  action_t do_init_default  = [] (const std::string&) { init_default(); };

  using namespace option;
  static auto opts = table(
      entry(
        names("help", "--help", "&HELP"), 
        "Display help for the \"init\" command.", 
        arg_none, 
        option::do_help),
      entry(
        names("--reset", "-R"),
        "Erase the entire database and the \".bit\" directory, then init.",
        arg_none,
        do_reset),
      entry(
        names("--remove", "-X"),
        "Erase the entire database and the \".bit\".",
        arg_none,
        do_remove),
      entry(do_init_default)
    );
  return (void*)&opts;
}

