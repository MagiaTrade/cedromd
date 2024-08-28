#include <iostream>

int main() {
  std::string username = CEDRO_USERNAME;
  std::string password = CEDRO_PASSWORD;
  std::string softKey = CEDRO_SOFTKEY;

  std::cout << "Username: " << username << "\n";
  std::cout << "Password: " << password << "\n";
  std::cout << "SoftKey: " << softKey << "\n";


  return EXIT_SUCCESS;
}