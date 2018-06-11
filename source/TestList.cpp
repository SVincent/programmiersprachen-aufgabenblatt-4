#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "List.hpp"

//Task 4.2

TEST_CASE ("test for size of list", "Task 4.2") {
    List<int> list;
    REQUIRE (list.size()== 0);
}

TEST_CASE ("test for empty list", "Task 4.2") {
    List<int> list;
    REQUIRE (list.empty()== true);
}

//Task 4.3
TEST_CASE ("test for push_front", "Task 4.3") {
    List<int> list;
    list.push_front(42);
    REQUIRE (42 == list.front());
    REQUIRE (list.size() == 1);
}

TEST_CASE ("test for push_back", "Task 4.3") {
    List<int> list;
    list.push_back(42);
    REQUIRE (42 == list.back());
    REQUIRE (list.size() == 1);
}

TEST_CASE ("test for pop_front", "Task 4.3") {
    List<int> list;
    list.push_front(42);
    list.push_back(43);
    REQUIRE (42 == list.front());
    REQUIRE (list.size() == 2);
    list.pop_front();
    REQUIRE (43 == list.front());
    list.pop_front();
    REQUIRE (list.empty());
}

TEST_CASE ("test for pop_back", "Task 4.3") {
    List<int> list;
    list.push_front(42);
    list.push_back(43);
    REQUIRE (43 == list.back());
    REQUIRE (list.size() == 2);
    list.pop_back();
    REQUIRE (42 == list.back());
    list.pop_back();
    REQUIRE (list.empty());
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}