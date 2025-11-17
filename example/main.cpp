#include <iostream>
#include <pqrs/cf/bundle.hpp>

int main(void) {
  // APPL
  {
    std::filesystem::path path("/System/Applications/Utilities/Terminal.app");
    if (auto type = pqrs::cf::bundle::get_package_type(path)) {
      std::cout << *type << ": " << path.string() << std::endl;
    }
  }

  // BNDL
  {
    std::filesystem::path path("/System/Library/Frameworks/Security.framework/Versions/A/MachServices/SecurityAgent.bundle");
    if (auto type = pqrs::cf::bundle::get_package_type(path)) {
      std::cout << *type << ": " << path.string() << std::endl;
    }
  }

  return 0;
}
