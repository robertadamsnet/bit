#ifndef DB_OBJECT_HPP_20151212170806
#define DB_OBJECT_HPP_20151212170806 

#include <string>
#include <fstream>
#include <map>
#include <functional>

class Database final {
public:
  using string_t        = std::string;
  
  using key_t           = string_t;
  using value_t         = string_t;

  using map_t           = std::map<key_t, value_t>;

  using record_t        = map_t::value_type;

  Database(const string_t& path);
  ~Database();

  auto operator[](const key_t& key) const -> const value_t&;
    
private:
  static auto from_file(const string_t& path) -> map_t;

  static auto record_from_string(const string_t& str) -> record_t;
  static auto record_from_string(size_t len, const char* cstr) -> record_t;

  map_t                 map_;

};

inline 
auto Database::operator[](const key_t& key) const -> const value_t& 
{
  return map_[key];
}

inline
Database::Database(const string_t& path)
  : map_(from_file(path))
{
   
}

inline
Database::~Database() 
{

}

inline
auto Database::from_file(const string_t& path) -> map_t {
  using namespace std;
  ifstream file(path);

  map_t db;

  string linebuf;

  while(true) {
    if(!getline(file, linebuf).good()) { break; }
    auto r = record_from_string(linebuf);
    db.erase(r.first);
    db.insert(r);
  }
  return db;
};

inline
auto Database::record_from_string(const string_t& s) -> record_t {
  return record_from_string(s.size(), s.c_str());
};

//============================================================================
//
inline
auto Database::record_from_string(size_t len, const char* cstr) -> record_t {
  size_t idx = 0;
  string_t key;

  auto getch =[&] {
    return idx < len ? cstr[idx++] : 0;
  };

  std::function<void(void)> process_key = [&] {
    auto ch = getch();
    switch(ch) {
    // terminate on delimiter or null
    case  0:
    case ':':
      return;
    // process extra char when escaped with '\'
    case '\\':
      ch = getch();
      break;
    };
    key.append(1, ch);
    // recurse
    process_key();
  };

  process_key();

  auto value_start  = idx < len ? idx     : len;
  
  return record_t(key, string_t(cstr + value_start));
}

#endif//DB_OBJECT_HPP_20151212170806
