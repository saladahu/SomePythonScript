#include <boost/regex.hpp>
#include <iostream>

int main() {
  std::cout << "Available regex syntaxes: \n"
            << "\t[0] Perl\n"
            << "\t[1] Perl case insensitive\n"
            << "\t[2] POSIX extended\n"
            << "\t[3] POSIX extended insensitive\n"
            << "\t[4] POSIX basic\n"
            << "\t[5] POSIX basic insensitive\n"
            << "Choose regex syntax: ";
  boost::regex::flag_type flag;
  switch (std::cin.get()) {
  case '0': flag = boost::regex::perl; break;
  case '1': flag = boost::regex::perl | boost::regex::icase; break;
  case '2': flag = boost::regex::extended; break;
  case '3': flag = boost::regex::extended | boost::regex::icase; break;
  case '4': flag = boost::regex::basic; break;
  case '5': flag = boost::regex::basic | boost::regex::icase; break;
  default:
    std::cout << "Incorrect number of regex syntax. Exiting...\n";
    return -1;
  }
  // disabling exceptions
  flag |= boost::regex::no_except;

  //restoring std::cin
  std::cin.ignore();
  std::cin.clear();
  std::string regex, str, replace_string;
  do {
    std::cout << "Input regex:";
    if (!std::getline(std::cin, regex) || regex.empty()) {
      return 0;
    }

    //without no_except flag this constructor may throw exceptions
    const boost::regex e(regex, flag);
    if (e.status()) {
      std::cout << "Incorrect regex pattern!\n";
      continue;
    }

    std::cout << "string to match: ";
    while (std::getline(std::cin, str) && !str.empty()) {
      boost::smatch results;
      bool matched = boost::regex_search(str, results, e);
      if (matched) {
        std::cout << "MATCH: ";
        std::copy(results.begin() + 1,
                  results.end(),
                  std::ostream_iterator<std::string>(std::cout, ","));
        std::cout << "\nReplace pattern: ";
        if (std::getline(std::cin, replace_string) &&
            !replace_string.empty()) {
          std::cout << "RESULT: "
                    << boost::regex_replace(str, e, replace_string);
        }
        else {
          std::cin.ignore();
          std::cin.clear();
        }
      }
      else {
        std::cout << "DOESNOT MATCH\n";
      }
      std::cout << "\nstring to match: ";
    }

    std::cin.ignore();
    std::cin.clear();
  } while (1);
  return 0;
}
