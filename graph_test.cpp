/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/dg/graph.h"
#include "catch.h"

// TODO(students): Fill this in.

SCENARIO("Creation of graph") {
  WHEN("Graphs constructed by same const_iterator with different order") {
    std::vector<std::string> a{"a", "b", "c", "d"};
    std::vector<std::string> b{"d", "a", "c", "b"};
    THEN("They should be equal") {
      gdwg::Graph<std::string, int> a{v.begin(), v.end()};
      gdwg::Graph<std::string, int> b{v.begin(), v.end()};
      REQUIRE(a == b);
    }
  }


    WHEN("Graphs constructed by iterators over tuples, and there are duplicate edges") {
      auto e1 = std::make_tuple(6, 500, 5.4);
      auto e2 = std::make_tuple(6, 500, 10.8);
      auto e3 = std::make_tuple(6, 500, 10.8);
      auto e = std::vector<std::tuple<int, int, double>>{e1, e2, e3};
      gdwg::Graph<int, double> g{e.begin(), e.end()};
      THEN("Duplicate edges should be removed") {
        auto result = g.GetWeights(6, 500);
        auto str = "";
        for (auto it = result.begin(); it != ss_5.end(); ++it) {
          str += *it + " ";
        }
        REQUIRE(str == "5.4 10.8 ");
    }
  }
}

SCENARIO("Insert nodes and edges") {
  WHEN("Insert duplicaet nodes/edges") {
    std::vector<std::string> a{"a", "b", "c", "d"};
    a.InsertNode("e");
    a.InsertNode("a");
    THEN("Duplicaet nodes/edges will not be added") {
      auto result = a.GetNodes();
      auto str = "";
        for (auto it = result.begin(); it != ss_5.end(); ++it) {
          str += *it + " ";
        }
      REQUIRE(str = = "a b c d e ");
    }
  }


    WHEN("Graphs constructed by iterators over tuples, and there are duplicate edges") {
      auto e1 = std::make_tuple(6, 500, 5.4);
      auto e2 = std::make_tuple(6, 500, 10.8);
      auto e3 = std::make_tuple(6, 500, 10.8);
      auto e = std::vector<std::tuple<int, int, double>>{e1, e2, e3};
      gdwg::Graph<int, double> g{e.begin(), e.end()};
      g.InsertEdge("6","500", 5.4)
      g.InsertEdge("6","500", 2.7)
      THEN("Duplicate edges should not be added") {
        auto result = g.GetWeights(6, 500);
        auto str = "";
        for (auto it = result.begin(); it != ss_5.end(); ++it) {
          str += *it + " ";
        }
        REQUIRE(str == "2.7 5.4 10.8");
    }
  }
}


