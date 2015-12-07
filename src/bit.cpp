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
      

  auto p = db::get_record("test:bunch of bullshit");

  cout << get<0>(p) << " == " << get<1>(p) << endl;
  return 0;
}
