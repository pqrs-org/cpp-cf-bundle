#include <boost/ut.hpp>
#include <pqrs/cf/bundle.hpp>
#include <unordered_map>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;
  using namespace std::literals;

  "get_package_type"_test = [] {
    // APPL
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/System/Applications/Utilities/Terminal.app");
      expect("APPL" == actual);
    }

    // BNDL
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/System/Library/Frameworks/Security.framework/Versions/A/MachServices/SecurityAgent.bundle");
      expect("BNDL" == actual);
    }

    // Not found
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/Applications/NotFound.app");
      expect(std::nullopt == actual);
    }
  };

  return 0;
}
