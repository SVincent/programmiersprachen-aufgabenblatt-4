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

//Task 4.4
TEST_CASE ("test for clean()" , "Task 4.4") {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.clear();
    REQUIRE (list.empty());
}

//Task 4.6
TEST_CASE ("test for begin(), end() on empty list", "Task 4.6") {
    List<int> list;
    auto b = list.begin();
    auto e = list.end();
    REQUIRE (b == e);
}

TEST_CASE ("test for begin(), end() on list with one element", "Task 4.6") {
    List<int> list;
    list.push_front(42);
    REQUIRE(42 == *list.begin());
} 

//Task 4.7
TEST_CASE ("test for list comparison, different size" , "Task 4.7") {
    List<int> list1;
    List<int> list2;
    list1.push_front(42);   
    REQUIRE (list1 != list2);
} 

TEST_CASE ("test for list comparison, same size" , "Task 4.7") {
    List<int> list1;
    List<int> list2;
    list1.push_front(42);  
    list2.push_front(42);   
    REQUIRE(list1 == list2);
    list1.push_front(42);  
    list2.push_front(43);   
    REQUIRE (list1 != list2);
} 

//Task 4.8
TEST_CASE ("test for copy constructor", "Task 4.8") {
    List<int> list; 
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    List<int> list2{list};
    REQUIRE (list == list2);
}

//Task 4.9
TEST_CASE ("test for insert()", "Task 4.9") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    ListIterator<int> li(list.begin());
    list.insert(li, 0);
    REQUIRE (list.front() == 0);
    list.clear();
    list.insert(li, 5);
    REQUIRE (list.front() == 5);
}

//Task 4.10
TEST_CASE ("test for reverse()", "Task 4.10") {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    List<int> list2 = reverse(list);
    list.reverse();
    REQUIRE (list.front() == 1);
    REQUIRE (list == list2);
    list.reverse();
    REQUIRE (list.front() == 4);
    REQUIRE (list != list2);
}

TEST_CASE ("test for std::copy to vector", "Task 4.11") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    //vector needs to have a size before using it, unless you want errors again
    std::vector<int> vector(list.size());
    std::copy(list.begin(), list.end(), vector.begin());
    REQUIRE (1 == *vector.begin());
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}