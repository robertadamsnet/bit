#include "bit.hpp"
#include "options.hpp"

#include <stdio.h>
#include <sys/stat.h>


int main (void)
{
  // try to create a .bit folder
  mkdir(".bit", 0775);

  // try to open the file for reading
  auto db_file = fopen(bit_db(), "r");
  if(db_file != nullptr) {
    fclose(db_file);
    printf("Database already initialized; aborting.\n");
    return -1;
  }

  // open the file for read/write
  db_file = fopen(bit_db(), "w+");
  if(db_file == nullptr) {
    printf("Could not create database file, '.bit/db'.  Aborting.\n");
    return -1;
  }

  fclose(db_file); 
  return 0;
}

