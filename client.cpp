#include <iostream>
#include <string>

#include "assignments/dg/graph.h"

// Note: At the moment, there is no client.sampleout. Please do your own testing

int main() {
  std::vector<std::string> v{"a", "b", "c", "d"};
  gdwg::Graph<std::string, int> a{v.begin(), v.end()};

  std::cout << "--- a --- \n" << a << "\n";

  std::string s1{"apple"};
  std::string s2{"orange"};
  std::string s3{"blueberry"};
  auto b11 = std::make_tuple(s1, s2, 5.4);
  auto b12 = std::make_tuple(s2, s3, 4.9);
  auto b2 = std::vector<std::tuple<std::string, std::string, double>>{b11, b12};
  gdwg::Graph<std::string, double> b{b2.begin(), b2.end()};

  std::cout << "--- b --- \n" << b << "\n";

  gdwg::Graph<char, std::string> c{'a', 'b', 'x', 'y'};
  std::cout << "--- c --- \n" << c << "\n";

  gdwg::Graph<std::string, double> d{b};
  std::cout << "--- d --- \n" << d << "\n";

  gdwg::Graph<std::string, double> e{std::move(d)};
  std::cout << "--- e --- \n" << e << "\n";

  std::cout << "--- d --- \n" << d << "\n";

  auto f = a;
  std::cout << "--- a --- \n" << a << "\n";
  std::cout << "--- f --- \n" << f << "\n";

  std::cout << "a ========= f \n" ;
  if (a == f) {
     std::cout << "a = f\n";
  } else if (a != f) {
     std::cout << "a != f\n";
  }

  auto g = std::move(a);
  std::cout << "--- a --- \n" << a << "\n";
  std::cout << "--- g --- \n" << f << "\n";

  auto boo1 = g.InsertNode("a");
  std::cout << boo1 << "\n";
  std::cout << "--- g --- \n" << g << "\n";
  auto boo2 = g.InsertNode("eeeeeee");
  std::cout << boo2 << "\n";
  std::cout << "--- g --- \n" << g << "\n";

  g.DeleteNode("b");
  g.InsertEdge("a","a", 5.5);
  std::cout << "--- g --- \n" << g << "\n";

  std::cout << "--- b --- \n" << b << "\n";
  b.MergeReplace("orange", "apple");
  std::cout << "--- b --- \n" << b << "\n";

  std::cout << "now clear";
  b.Clear();
  std::cout << "--- b --- \n" << b << "\n";

  f.Clear();
  std::cout << "a ========= f \n" ;
  if (a == f) {
     std::cout << "a = f\n";
  } else if (a != f) {
     std::cout << "a != f\n";
  }

  auto ss11 = std::make_tuple(500, 10, 5.4);
  auto ss12 = std::make_tuple(10, 200, 4.9);
  auto ss13 = std::make_tuple(6, 500, 10.8);
  auto ss14 = std::make_tuple(6, 500, 10.8);
  auto ss15 = std::make_tuple(500, 6, 9.9);
  auto ss2 = std::vector<std::tuple<int, int, double>>{ss11, ss12, ss13, ss14, ss15};
  gdwg::Graph<int, double> ss{ss2.begin(), ss2.end()};
  std::cout << "--- ss --- \n" << ss << "\n";

  auto ss_1 = ss.IsNode(500);
  std::cout << "--- ss_1 --- \n" << ss_1 << "\n";
  auto ss_2 = ss.IsConnected(500, 10);
  std::cout << "--- ss_2 --- \n" << ss_2 << "\n";
  auto ss_3 = ss.IsConnected(500, 200);
  std::cout << "--- ss_3 --- \n" << ss_3 << "\n";
  std::cout << "--- ss_4---- \n";
  auto ss_4 = ss.GetNodes();
  for (auto it = ss_4.begin(); it != ss_4.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";
  std::cout << "--- ss_5---- \n";
  auto ss_5 = ss.GetConnected(500);
  for (auto it = ss_5.begin(); it != ss_5.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";
  std::cout << "--- ss_6---- \n";
  auto ss_6 = ss.GetWeights(500, 10);
  for (auto it = ss_6.begin(); it != ss_6.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  // gdwg::Graph<std::string, int> g;
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
