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
    // STOP AND LOOK FOR THE FREE FUNCTION CALL.
    // Whatever you are doing, stop right now and look.
    // Or replace the getcwd function with the boost solution, which is
    // pretty ugly.
    auto cwd = getcwd(nullptr, 0);
    db_link << cwd << "\n";
    // Here's the free function call.  All is well.
    free(cwd);
  };

  auto exec = [&] (const std::string& cmdline) {
    std::cout << cmdline << "\n";
    std::system(cmdline.c_str());
  };

  bool link_output_stale = false;
  auto compile = [&] (const std::string& source, const std::string& output) 
  {
    auto source_time = filesystem::last_write_time(source);
    auto output_time = filesystem::last_write_time(output);
    bool output_stale = output_time < source_time;
    if(output_stale) {
      link_output_stale = true;
      std::stringstream cmdline;
      cmdline << db["@CPP_COMPILER"]
              << " -c " << source
              << " -o " << output;  
      exec(cmdline.str());
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
      cmdline << db["@CPP_COMPILER"]
              << " -o " << cpp_build_path << "/" << db["@LINK_OUTPUT"]
              << " " << output_list;
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
