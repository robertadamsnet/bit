#include "types.hpp"
#include "db.hpp"
#include "db_keys.hpp"

#include <functional>
#include <iostream>

auto prefix_list = [] (auto&& prefix, auto&& db_key) {
  auto list = db[db_key];
  using types::string_t;

  string_t include_opts;

  function<void(const string_t&)> recurse_list = [&] (const string_t& s) {
    auto record = db::from_string(s);
    if(!record.first.empty()) {
      include_opts += prefix + record.first;
      if(!record.second.empty()) {
        recurse_list(record.second);
      }
    }
  };

  recurse_list(list);

  return include_opts;
};

int main(int argc, char* argv[]) {
  using namespace std;

  auto db = db::from_file(db::config::dir());

  cout << prefix_list("-I", db::key_bit_dirs_include()) << endl;
  return 0;
};


