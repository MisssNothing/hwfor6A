#include <iostream>
#include <iomanip>
#include "vector-top-it.hpp"

using topit::Vector;
bool test1() {
  Vector< int > v;
  return v.isEmpty();
}
bool test2() {
  Vector< int > v;
  return v.getSize() == 0;
}
bool test3() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  return v.getSize() == size;
}

bool test4() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  try {
    int& value = v.at(0);
    return value == 1;
  } catch (... ) {
    return false;
  }
}

bool test5() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  try {
    v.at(size + 1);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool test6() {
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 1);
  try {
    const int& value = v.at(0);
    return value == 1;
  } catch (... ) {
    return false;
  }
}

bool test7() {
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 0);
  try {
    v.at(size + 1);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool test8() {
  Vector< int > v(2, 0);
  Vector< int > yav = v;
  return yav == v;
}

bool test9() {
  Vector< int > v;
  Vector< int > yav(2, 0);
  bool res = v != yav;
  v = yav;
  return res && v == yav;
}

bool test10() {
  Vector< int > v(2, 0);
  Vector< int > yav(3, 1);

  Vector< int > cpy_v(v);
  Vector< int > cpy_yav(yav);
  v.swap(yav);

  return cpy_v == yav && cpy_yav == v;
}

bool test11() {
  Vector< int > v(2, 0);
  Vector< int > cpy_v(v);

  Vector< int > yav = std::move(v);
  return yav == cpy_v;
}

bool test12() {
  Vector< int > v(2, 0);
  Vector< int > cpy(v);
  Vector< int > yav;

  yav = std::move(v);
  return yav == cpy;
}

bool test13() {
  Vector<int> v1(3, 5);
  Vector<int> v2;
  v2 = v1;
  return v2 == v1 && v2.getSize() == 3 && v2[0] == 5 && v2[2] == 5;
}

bool test14() {
  Vector<int> v(3, 42);
  Vector<int> original(v);
  v = v;
  return v == original && v[0] == 42 && v.getSize() == 3;
}

bool test15() {
  Vector<int> v1;
  Vector<int> v2(5, 10);
  v1 = v2;
  return v1.getSize() == 5 && v1[0] == 10 && v1[4] == 10;
}

bool test16() {
  Vector<int> v1(5, 10);
  Vector<int> v2;
  v1 = v2;
  return v1.isEmpty() && v2.isEmpty() && v1.getSize() == 0;
}

bool test17() {
  Vector<int> v1(2, 1);
  Vector<int> v2(4, 2);
  v1 = v2;
  if (v1.getSize() != 4) return false;
  for (size_t i = 0; i < 4; ++i) {
    if (v1[i] != 2) return false;
  }
  return true;
}

bool test18() {
  Vector<std::string> v1(3, "hello");
  Vector<std::string> v2(5, "world");
  try {
    v1 = v2;
    return v1.getSize() == 5 && v1[0] == "world" && v1[4] == "world";
  } catch (...) {
    return false;
  }
}

bool test19() {
  Vector<int> original(4, 100);
  Vector<int> copy(original);
  return copy == original && copy[0] == 100 && copy[3] == 100;
}

int main() {
  using test_t = bool(*)();
  using case_t = std::pair< test_t, const char* >;
  case_t tests[] = {
    { test1, "Default constructed vector is empty" },
    { test2, "Default constructed vector size is zero" },
    { test3, "Vector constructed with size has non-zero size" },
    { test4, "In range access does not generate exceptions" },
    { test5, "Out of range access generates std::out_of_range exception" },
    { test6, "In range access for const vector: same as non-const" },
    { test7, "Out of range access for const vector: same as non-const" },
    { test8, "Copy constructor"},
    { test9, "Copy assignment operator"},
    { test10, "Swap for two vectors"},
    { test11, "Move constructor"},
    { test12, "Move assignment operator"},
    { test13, "13. Copy/Swap: basic assignment" },
    { test14, "14. Copy/Swap: self-assignment safety" },
    { test15, "15. Copy/Swap: empty to non-empty" },
    { test16, "16. Copy/Swap: non-empty to empty" },
    { test17, "17. Copy/Swap: different sizes" },
    { test18, "18. Copy/Swap: exception safety" },
    { test19, "19. Copy/Swap: copy constructor" },
  };

  size_t count = sizeof(tests) / sizeof(case_t);

  std::cout << std::boolalpha;
  bool result = true;
  size_t successes = 0, fails = 0;
  for (size_t i = 0; i < count; ++i) {
    bool case_result = tests[i].first();
    successes += case_result;
    fails += !case_result;
    result = result && case_result;
    std::cout << case_result;
    std::cout << ": ";
    std::cout << tests[i].second << "\n";
  }
  std::cout << "SUMMARY\n";
  std::cout << result << ": TEST RESULTS\n";
  std::cout << fails << ": failed tests\n";
  std::cout << successes << ": passed tests\n";
}
