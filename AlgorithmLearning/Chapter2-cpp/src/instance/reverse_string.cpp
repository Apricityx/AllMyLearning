#include <iostream>

#include <ostream>
#include <string>
using namespace std;
string reverse_string(const string &str) {
  if (str.size() <= 1) {
    return str;
  }
  return reverse_string(str.substr(1)) + str[0];
}