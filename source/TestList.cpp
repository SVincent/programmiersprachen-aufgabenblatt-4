#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "List.hpp"

//Task 4.2

TEST_CASE ("test for size of list", "Task 4.2") {
    List<int> lista;
    REQUIRE (lista.size()== 0);
}

TEST_CASE ("test for empty list", "Task 4.2") {
    List<int> listb;
    REQUIRE (listb.empty()== true);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}