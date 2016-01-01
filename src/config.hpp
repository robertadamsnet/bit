#ifndef CONFIG_HPP_20151230091723
#define CONFIG_HPP_20151230091723 

#include "db.hpp"
#include <boost/filesystem.hpp>
#include <fstream>

namespace config {

  namespace system {
    using string = std::string;
    static string db_folder = ".bit/";
    static string db_path   = db_folder + "db";
    static string db_link_filename = ".db_link";
  }; // namespace system

  namespace fn {
    using namespace boost::filesystem;
    inline void locate_database() {
      
      if(exists(system::db_path)) {
        return;
      } else if(exists(system::db_link_filename)) {
        std::fstream db_link(system::db_link_filename);
        std::string bit_db_path;
        std::getline(db_link, bit_db_path);
        bit_db_path += "/";
        current_path(bit_db_path);
      } else {
        std::string msg = "Bit database not initialized.";
        throw std::runtime_error(msg);
      }
    }
    inline auto read_db() {
      locate_database();
      return db::from_file(system::db_path);
    };
    inline auto write_db(const db::map_t& db) {
      return db::to_file(system::db_path, db);
    };
    template<class T>
    auto remove_from_db(const T& keys) {
      auto db = config::fn::read_db();
      for(const auto& k : keys) {
        db.erase(k);
      }
      config::fn::write_db(db);
    };
    inline auto merge_into_db(const db::map_t& src) {
      auto db = config::fn::read_db();
      for(const auto& record : src) {
        auto existing_key = db.find(record.first);
        if(existing_key != db.end()) {
          db.erase(existing_key);
        }
        db.insert(record);
      };

      config::fn::write_db(db);
    }
  }; // namespace fn

  inline
  auto defaults() -> db::map_t {
    using namespace db;
    return {
      // c++ compiler options
      record_t("@CPP_COMPILER", "/usr/bin/clang++"),
      record_t("@CPP_INCLUDE_DIRECTORIES", ""),
      // linker options
      record_t("@LINK_LINKER", "/usr/bin/ld"),
      record_t("@LINK_DIRECTORIES", ""),
      // build system info
      record_t("&VERSION", "0:1")
    };
  };

}; // namespace config

#endif//CONFIG_HPP_20151230091723
