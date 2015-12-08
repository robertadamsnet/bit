#include "record.hpp"
#include "db.hpp"
#include <fstream>

namespace db {
//============================================================================
//

auto from_file(const string_t& path) -> map_t {
  using namespace std;
  ifstream file(path);
  map_t db;

  string linebuf;
  while(true) {
    if(!getline(file, linebuf).good()) break;
    db.insert(record::from_string(linebuf));
  }
  return db;
};

auto to_file(const string_t& path, const map_t& db) -> void {
  using namespace std;
  ofstream file(path);

  for(const auto& r : db) {
    file << record::to_string(r) << "\n";
  }
}

//============================================================================
}; // namespace db
