#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include <tuple>


namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
  class const_iterator {};

//Constructors & Destructors
    Graph<N, E>() {}
    	
    Graph<N, E>(typename std::vector<N>::const_iterator begin, 
                typename std::vector<N>::const_iterator end
        ) {
            for (auto it = begin; it != end; ++it) {
                auto node_tmp = std::make_unique <N[]>(1);
                node_tmp[0] = *it;
                node_.push_back(std::move(node_tmp));
        }
    }

    Graph<N, E>(
        typename std::vector<std::tuple<N, N, E>>::const_iterator begin,
        typename std::vector<std::tuple<N, N, E>>::const_iterator end
        ) {
            for (auto it = begin; it != end; ++it) {
                auto node_tmp_0 = std::make_unique <N[]>(1);
                auto node_tmp_1 = std::make_unique <N[]>(1);
                node_tmp_0[0] = std::get<0>(*it);
                node_tmp_1[0] = std::get<1>(*it);
                node_.push_back(std::move(node_tmp_0));
                node_.push_back(std::move(node_tmp_1));
                // std::unique_ptr<E[]> edge_tmp = std::make_unique <E[]>(3);
                // edge_tmp[0] = std::get<0>(*it);
                // edge_tmp[1] = std::get<1>(*it);
                // edge_tmp[2] = std::get<2>(*it);
                auto edge_tmp = std::make_unique <std::tuple<N, N, E>[]>(1);
                edge_tmp[0] = *it;
                edge_.push_back(std::move(edge_tmp));
            }
        }

    Graph<N, E>(typename std::initializer_list<N> source) {
        for (auto it = source.begin(); it != source.end(); ++it) {
            auto node_tmp = std::make_unique <N[]>(1);
                node_tmp[0] = *it;
                node_.push_back(std::move(node_tmp));
        }
    }

    Graph<N, E>(const gdwg::Graph<N, E>& source) {
        for (auto it = source.node_.begin(); it != source.node_.end(); ++it) {
            auto node_tmp = std::make_unique <N[]>(1);
            node_tmp[0] = (*it)[0];
            node_.push_back(std::move(node_tmp));
        }
        for (auto it = source.edge_.begin(); it != source.edge_.end(); ++it) {
            auto edge_tmp = std::make_unique <std::tuple<N, N, E>[]>(1);
            edge_tmp[0] = (*it)[0];
            edge_.push_back(std::move(edge_tmp));
        }
    }

    // Graph<N, E>(gdwg::Graph<N, E>&& source)


    friend std::ostream& operator<<(std::ostream& os, const gdwg::Graph<N, E>& g){
        for (auto it_n = g.node_.begin(); it_n != g.node_.end(); ++it_n) {
            os << (*it_n)[0] << "(\n"; 
            for (auto it_e = g.edge_.begin(); it_e != g.edge_.end(); ++it_e) {
                if ((*it_n)[0] == std::get<0>((*it_e)[0])) {
                    os << "  " << std::get<1>((*it_e)[0]) << " | " << std::get<2>((*it_e)[0]);
                }
            }
            os << "\n)\n";
        }
        return os;
    }


 private:
    std::vector <std::unique_ptr<N[]>> node_;
    std::vector <std::unique_ptr<std::tuple<N, N, E>[]>> edge_;
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
