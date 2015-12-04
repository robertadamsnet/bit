#ifndef MERGE_OPTS_HPP_2015_1203_011244
#define MERGE_OPTS_HPP_2015_1203_011244 

inline
auto merge_opts(int argc, const char* argv[]) -> std::string {
  std::string s;
  s += argv[0];
  for(int i = 1; i < argc; ++i) {
    s += argv[i];
    s += " ";
  }
  return s;
}

#endif//MERGE_OPTS_HPP_2015_1203_011244
