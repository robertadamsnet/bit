#ifndef BUILD_ENVIRONMENT_HPP_20151212053440
#define BUILD_ENVIRONMENT_HPP_20151212053440 

//! \brief This class is responsible for maintaining the state of the build
//!        configuration.
/*!
           BuildEnv is a convenience class, not an interface; therefore,
           it is marked 'final' to prevent any attempts at using it in some
           wacky polymorphic love triangle.  You can't copy it, you can't
           move it, and if you try to use it beyond a local context, you're
           probably gonna break it.  So you really shouldn't use it anywhere
           but the 'main' function.
 */
class BuildEnv final {
public:
  using db_t        = db::map_t;

  static constexpr auto db_path        = ".bin/db";

  BuildEnv();

  ~BuildEnv();

  auto db_commit() -> void;

  auto compile() -> int;

private:
  db_t db_;

  auto compile_options() -> int;
};

inline
BuildEnv::BuildEnv() 
  : db_(db::from_file(db_path))
{
};

inline
BuildEnv::~BuildEnv()
{
  db_commit();
};

inline
auto BuildEnv::db_commit() -> void {
  db::to_file(db_path, db_);
};


inline
auto BuildEnv::compile() -> int {
  auto opts = compile_options();
  
};

#endif//BUILD_ENVIRONMENT_HPP_20151212053440
