#ifndef RESOURCE_HPP_20151211150340
#define RESOURCE_HPP_20151211150340 

namespace resource {

  auto make = [] (auto&& ctor, auto&& dtor) {
    using ctor_t = decltype(ctor);
    
    using resource_t = decltype(ctor());

    using dtor_t = decltype(dtor);
    struct resource_obj {
      resource_obj(ctor_t ct, dtor_t dt) : dtor_(dt) {
        ct();
      }
      ~resource_obj() {
        dtor_(resource_);
      }

      const resource_t& operator()() const {
        return resource_;
      }

      resource_t resource_;
      dtor_t dtor_;
    };
    return resource_obj(ctor, dtor);
  };

}; // namespace resource
#endif//RESOURCE_HPP_20151211150340
