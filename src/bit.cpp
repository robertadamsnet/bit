#include <iostream>
#include <functional>
#include <vector>

struct Options {
  template<class T>
  using function_t = std::function<T>;
  
  using option_str_fn = function_t<const char*(void)>;
  
  using string_t = std::string;

  using options_t = std::vector<string_t>;

  static auto parse(int argc, char* argv[]) -> const options_t&; 

};

int main(int argc, char* argv[]) {
  using namespace std;
  for(int a; a < argc; ++a) {
    cout << argv[a];
  }
  cout << "\n";
}

auto Options::parse(int argc, char* argv[]) -> const options_t& {
  options_t options;
  unsigned arg_index = 0;
  char* arg = argv[arg_index];
  char* opt = arg;

  auto get_opt_text = [&] () {
    return *opt;
  };

  std::function<void(void)> parse_opt;

  auto push_option = [&](const char* chars...) {

    std::function<void(void)> inner_ = [&]() {
      char* optstr = { head, inner_(tail...) };
      return optstr;
    };
    return inner_();
  };

  auto parse_short_options = [&]() {
    ++opt;
    auto ch = *opt;
    switch(ch) {
    case '0':
      push_option
      return parse_opt();
      break;
    case '-':
      
      return parse_opt;
      break;
    default:
      if(isalpha(ch)) {
        char* short_opt = { '-', ch, 0 };
        options.push_back(short_opt);
        return parse_short_options();
      }
      return get_opt_text();
    };
  };

  parse_opt = [&]() {
    switch(*opt) {
    case 0:
      if(arg_index < argc) { 
        arg = argv[++arg_index];
        opt = arg;
        return parse_opt();
      } else {
        return opt;
      }
      break;
    case '-':
      parse_short_options();
      break;
    default:
      return get_opt_text();
    };
    
  }; 
  auto next_arg = [&](int a) {
    parse_opt(current_arg);

  }
};
