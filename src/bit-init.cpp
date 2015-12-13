#include "db.hpp"
#include "option.hpp"
#include "resource.hpp"
#include "config.hpp"

#include <sys/stat.h>
#include <iostream>
#include <boost/filesystem.hpp>

auto do_reset = [](const opt::string_t& s) {
  using namespace std;
  cout << "Re-initializing database to defaults." << endl;
  auto defaults = db::init_defaults();
  db::to_file(db::config::path(), defaults);
  return 0;
};

auto do_non_opt = [](const opt::string_t& s) {
  
  return 0;
};

auto do_init = []() {
  using namespace boost::filesystem;
  using namespace std;

  auto db_path = db::config::path();
  auto db_dir  = db::config::dir();

  if(!is_directory(db_dir)) {
    try { create_directory(db_dir); }
    catch (...) {
      cerr << "Could not create \"" << db_dir << "\" directory." << endl;
      return -1;
    }
  }
  if(exists(db_path)) {
    cerr << "Database already exists." << endl;
    return -1;
  }

  cout << "Initializing database \"" << db_path << "\"" << endl;
  auto defaults = db::init_defaults();
  db::to_file(db_path, defaults);
  return 0;
};

int main (int argc, char* argv[]) 
{

  auto opts = opt::make_list(
    opt::make('R', "reset", "Clear database entries and re-initialize keys.", 
      opt::arg_none, do_reset)
  );
  return opt::parse(opts, do_non_opt, do_init)(argc, argv);
}

