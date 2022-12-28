#include "set.hpp"
#include <iostream>

int main(int argc, char **argv) {
  int n;
  std::cin >> n;
  StringHasher h;
  Set<std::string, StringHasher> hash_set(n, h);
  char operation;
  std::string key;
  std::string value;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> operation >> key;
    switch (operation) {
    case '+':
      std::cin >> value;
      std::cout << (hash_set.add(key, value) ? "OK" : "FAIL") << "\n";
      break;
    case '-':
      std::cout << (hash_set.remove(key) ? "OK" : "FAIL") << "\n";
      break;
    case '?':
      std::cout << (hash_set.get(key)) << "\n";
      break;
    }
  }
  return 0;
}
