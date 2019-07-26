#include <iostream>
#include <string>

#include "assignments/dg/graph.h"

// Note: At the moment, there is no client.sampleout. Please do your own testing

int main() {
  std::vector<std::string> v{"a", "b", "c", "d"};
  gdwg::Graph<std::string, int> a{v.begin(), v.end()};

  std::cout << a << '\n';

  std::string s1{"apple"};
  std::string s2{"orange"};
  auto e1 = std::make_tuple(s1, s2, 5.4);
  auto e = std::vector<std::tuple<std::string, std::string, double>>{e1};
  gdwg::Graph<std::string, double> b{e.begin(), e.end()};

  std::cout << b << '\n';

  gdwg::Graph<char, std::string> c{'a', 'b', 'x', 'y'};
  std::cout << c << '\n';

  gdwg::Graph<std::string, double> d{b};
  std::cout << d << '\n';


  // g.InsertNode("hello");
  // g.InsertNode("how");
  // g.InsertNode("are");
  // g.InsertNode("you?");

  // g.InsertEdge("hello", "how", 5);
  // g.InsertEdge("hello", "are", 8);
  // g.InsertEdge("hello", "are", 2);

  // g.InsertEdge("how", "you?", 1);
  // g.InsertEdge("how", "hello", 4);

  // g.InsertEdge("are", "you?", 3);

  // std::cout << g << '\n';

  // gdwg::Graph<std::string, int> g2{g};

  // std::cout << g2 << "\n";

  // // This is a structured binding.
  // // https://en.cppreference.com/w/cpp/language/structured_binding
  // // It allows you to unpack your tuple.
  // for (const auto& [from, to, weight] : g) {
  //   std::cout << from << " -> " << to << " (weight " << weight << ")\n";
  // }
}
