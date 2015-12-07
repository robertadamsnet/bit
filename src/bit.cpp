#include "bit.hpp"
#include "db.hpp"
#include <iostream>


int main()
{
  using namespace std;
  cout << "Not supporting the 'bit' command right now.  Try one of the following:\n"
       << "\n\n...um...I don't feel like adding code to list the commands right now.\n"
       << "so just type \"ls\"\n\n"
       << "In the meantime, here is some test crap: " << endl;
      

  db::string_t source = "test\\:delim:bunch of bullshit";
  cout << "Source:\n" << source << "\n";


  auto record = db::record_from_string(source);
  cout << "Key = \""    << record.first  << "\" "
       << "Value = \""  << record.second << "\"\n";

  auto line = db::string_from_record(record);

  cout << "Converted back to string:\n"
       << line << "\n";
  return 0;
}
