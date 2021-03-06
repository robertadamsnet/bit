#ifndef CMD_BUILD_HPP_201512301844
#define CMD_BUILD_HPP_201512301844 

#include "config.hpp"
#include <unistd.h>
#include <options/options.hpp>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>

void build();

inline
auto cmd_build_opt_table() -> option::table_t* {
  using namespace option;

  auto do_any = [&] (const std::string& s) {
    std::stringstream msg;
    msg << "Unexpected symbol: " << s;
    throw std::runtime_error(msg.str());
  };

  auto do_build = [&] (const std::string&) {
    build();
  };

  static auto opts = table(
    entry(tag_nomatch(), do_any),
    entry(do_build)
  );

  

  return &opts;
};

inline
auto for_each_string(const std::string& list, 
    const std::function<void(const std::string&)>& action) -> void
{
  if(list.size()) {
    auto record = db::from_string(list);
    const auto& head = record.first;
    const auto& tail = record.second;
    action(head);
    for_each_string(tail, action);
  }
};

inline
auto link_libraries(db::map_t& db) -> std::string {
  std::stringstream ss;
  ss << "-Wl";
  int insert_comma = 0;
  auto add_library = [&] (const std::string& s) {
    ss << ",-l" << s;
  };

  auto link_libraries = db["@LINK_LIBRARIES"];
  boost::trim(link_libraries);
  for_each_string(link_libraries, add_library);
  return ss.str();
};

inline
auto link_options(db::map_t& db) -> std::string {
  std::string buf;
  buf += link_libraries(db);
  return buf;
};

inline
auto cpp_include_paths(db::map_t& db) -> std::string {
  std::string buf;

  auto add_path = [&] (const std::string& p) {
    buf += "-I" + p;
  };

  for_each_string(db["@CPP_INCLUDE_DIRECTORIES"], add_path);
  return buf;
};

inline
void build() {
  using namespace boost;
  // load database
  auto db = config::fn::read_db();

  // path to build directory
  auto cpp_build_path(db["@CPP_BUILD_PATH"]);

  auto enter_build_dir = [&] {
    if(!filesystem::exists(cpp_build_path)) {
      filesystem::create_directory(cpp_build_path);
    };
    std::string db_link_path = 
      cpp_build_path + "/" + config::system::db_link_filename;
    std::ofstream db_link(db_link_path, std::ios::out | std::ios::trunc);
    // MEMORY GETS MALLOC'd HERE.
    // DO NOT SUBVERT THE TRY-CATCH BLOCKS, unless you want a memory leak.
    struct unique_throwaway_type;
    char* cwd = nullptr;
    try {
      cwd = getcwd(nullptr, 0);
      db_link << cwd << "\n";
      free(cwd);
    } catch(...) {
      free(cwd);
      throw;
    }
  };

  auto exec = [&] (const std::string& cmdline) {
    std::cout << cmdline << "\n";
    auto result = std::system(cmdline.c_str());
    if(result) {
      std::string msg = "Build terminated.";
      throw std::runtime_error(msg);
    }
  };

  bool link_output_stale = false;
  auto compile = [&] (const std::string& source, const std::string& output) 
  {
    bool output_stale = false;
    try {
      auto source_time = filesystem::last_write_time(source);
      auto output_time = filesystem::last_write_time(output);
      output_stale = output_time < source_time;
    } catch(...) {
      output_stale = true;
    }
    if(output_stale) {
      std::stringstream cmdline;
      cmdline << db["@CPP_COMPILER"]
              << " -c " << source
              << " -o " << output
              << " "    << db["@CPP_FLAGS"]
              << " "    << cpp_include_paths(db);
      exec(cmdline.str());
    }
    try {
      auto output_time = filesystem::last_write_time(output);
      auto target = db["@TARGET"];
      auto target_time = filesystem::last_write_time(target);
      link_output_stale = target_time < output_time;
    } catch (...) {
      link_output_stale = true;
    }
  };


  using action_t = std::function<void(const std::string&, const std::string&)>;
  std::string output_list;
  std::function<void(const std::string&, const action_t&)> 
    for_each_source = [&] (const std::string& sources, const auto& action) 
  {
    auto record = db::from_string(sources);
    const auto& source = record.first;
    const auto& tail = record.second;
    auto output = cpp_build_path + "/" + source + ".o";
    output_list += " " + output; 
    action(source, output);
    if(!record.second.empty()) {
      for_each_source(tail, action);
    }
  };

  auto link = [&] {
    if(link_output_stale) {
      std::stringstream cmdline;
      auto link_output = db["@TARGET"];
      boost::trim(link_output);
      if(link_output.empty()) {
        std::string msg = "Target name not specified.";
        throw std::runtime_error(msg);
      }
      cmdline << db["@CPP_COMPILER"]
              << " -o " << cpp_build_path << "/" <<  link_output
              << " " << output_list
              << " " << link_options(db);
      exec(cmdline.str());
    } else {
      std::cout << "All output files up-to-date.\n";
    }
  };

  enter_build_dir(); 

  auto sources = db["@CPP_SOURCES"];

  for_each_source(sources, compile);
  link();

}
#endif//CMD_BUILD_HPP_201512301844
