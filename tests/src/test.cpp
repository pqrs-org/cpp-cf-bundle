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
      expect(pqrs::cf::bundle::package_type_application == actual);
    }

    // FMWK
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/System/Library/Frameworks/Security.framework");
      expect(pqrs::cf::bundle::package_type_framework == actual);
    }

    // BNDL
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/System/Library/Frameworks/Security.framework/Versions/A/MachServices/SecurityAgent.bundle");
      expect(pqrs::cf::bundle::package_type_bundle == actual);
    }

    // Not found
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/Applications/NotFound.app");
      expect(std::nullopt == actual);
    }

    // Not bundle
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/bin/ls");
      expect(std::nullopt == actual);
    }
  };

  "application"_test = [] {
    // APPL
    {
      expect(true == pqrs::cf::bundle::application(
                         "/System/Applications/Utilities/Terminal.app"));
    }

    // FMWK
    {
      expect(false == pqrs::cf::bundle::application(
                          "/System/Library/Frameworks/Security.framework"));
    }

    // BNDL
    {
      expect(false == pqrs::cf::bundle::application(
                          "/System/Library/Frameworks/Security.framework/Versions/A/MachServices/SecurityAgent.bundle"));
    }

    // Not found
    {
      expect(false == pqrs::cf::bundle::application(
                          "/Applications/NotFound.app"));
    }
  };

  return 0;
}
