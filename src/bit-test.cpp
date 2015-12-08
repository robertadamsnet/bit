#include "bit.hpp"
#include "option.hpp"
#include "db.hpp"
#include "record.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
  using namespace std;
  using db::map_t;
  using record::record_t;

  map_t test1 = {
    record_t("name", "Robert"),
    record_t("age", "29"),
    record_t("escape-char-test\\:end-test", "dummy value")
  }; 


  cout << "Writing test structure 'test1' to file.\n";
  db::to_file("test1", test1);

  cout << "Reading 'test1' into new structure 'test1_new'.\n";
  auto test1_new = db::from_file("test1");

  cout << "Comparing structures...\n";

  auto record = test1.begin();
  auto new_record = test1_new.begin();
  while(record != test1.end() && new_record != test1_new.end()) {
    if(*record != *new_record) {
      auto dump = [&] (auto&& r) { cout << "[" << r.first  << "]"
                                        << "[" << r.second << "]"; };
      dump(*record);
      cout << ":";
      dump(*new_record);
      cout << "\n";
    }
    ++record;
    ++new_record;
  };

  options::merge(argc, argv);

  return 0;
}
