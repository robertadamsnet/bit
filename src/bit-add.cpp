#include "bit.hpp"
#include "options.hpp"
#include <csv.hpp>
#include <fstream>
#include <map>

using namespace std;

auto catcher(const string& s) -> void;
auto globals() -> std::map<string, string>&;

int main(int argc, char* argv[]) {
  auto in = std::ios::in;
  auto out = std::ios::out; 
  fstream f(".bit/db.csv", in|out);

  auto getline = [&] () {
    string l;
    std::getline(cin, l);
    if(cin.good() == false) {
      return string();
    }
    return l;
  };

  csv::callback_t cb = [&](const csv::record_t& r) {
    cout << get<0>(r) << "="
         << get<1>(r) << ":";
    for(auto& i : get<2>(r)) {
      cout << ":" << i;
    }
    cout << "\n";
  };

  csv::parse(getline, cb);
  
  return 0;
}

