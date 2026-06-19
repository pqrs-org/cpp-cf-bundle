#include <boost/ut.hpp>
#include <pqrs/cf/bundle.hpp>
#include <unordered_map>

int main() {
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

    // FNDR
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/System/Library/CoreServices/Finder.app");
      expect(pqrs::cf::bundle::package_type_finder == actual);
    }

    // With white space
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/System/Applications/Utilities/Activity Monitor.app");
      expect(pqrs::cf::bundle::package_type_application == actual);
    }

    // Not found
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/Applications/NotFound.app");
      expect(std::nullopt == actual);
    }

    // Not found (guess_if_missing_package_type)
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/Applications/NotFound.app",
          true);
      expect(std::nullopt == actual);
    }

    // Not bundle
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/bin/ls");
      expect(std::nullopt == actual);
    }

    // Not bundle (guess_if_missing_package_type)
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "/bin/ls",
          true);
      expect(std::nullopt == actual);
    }

    // No CFBundlePackageType
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "data/NoBundlePackageType.app");
      expect(std::nullopt == actual);
    }

    // No CFBundlePackageType (guess_if_missing_package_type)
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "data/NoBundlePackageType.app",
          true);
      expect(pqrs::cf::bundle::package_type_application == actual);
    }

    // No CFBundlePackageType (guess_if_missing_package_type, framework)
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "data/NoBundlePackageType.framework",
          true);
      expect(pqrs::cf::bundle::package_type_framework == actual);
    }

    // No CFBundlePackageType (guess_if_missing_package_type, bundle fallback)
    {
      auto actual = pqrs::cf::bundle::get_package_type(
          "data/NoBundlePackageType.bundle",
          true);
      expect(pqrs::cf::bundle::package_type_bundle == actual);
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

    // With white space
    {
      expect(true == pqrs::cf::bundle::application(
                         "/System/Applications/Utilities/Activity Monitor.app"));
    }

    // Not found
    {
      expect(false == pqrs::cf::bundle::application(
                          "/Applications/NotFound.app"));
    }

    // No CFBundlePackageType (guess)
    {
      expect(true == pqrs::cf::bundle::application(
                         "data/NoBundlePackageType.app"));
    }

    // No CFBundlePackageType (guess, framework)
    {
      expect(false == pqrs::cf::bundle::application(
                          "data/NoBundlePackageType.framework"));
    }

    // No CFBundlePackageType (guess, bundle fallback)
    {
      expect(false == pqrs::cf::bundle::application(
                          "data/NoBundlePackageType.bundle"));
    }
  };

  return 0;
}
