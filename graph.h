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

    //Default Constructor
    Graph<N, E>() {}
    	
    Graph<N, E>(typename std::vector<N>::const_iterator begin, 
                typename std::vector<N>::const_iterator end
        ) noexcept {
            for (auto it = begin; it != end; ++it) {
                auto node_tmp = std::make_unique <N[]>(1);
                node_tmp[0] = *it;
                node_.push_back(std::move(node_tmp));
        }
        sort();
    }

    Graph<N, E>(
        typename std::vector<std::tuple<N, N, E>>::const_iterator begin,
        typename std::vector<std::tuple<N, N, E>>::const_iterator end
        ) noexcept {
            for (auto it = begin; it != end; ++it) {
                auto node_tmp_0 = std::make_unique <N[]>(1);
                auto node_tmp_1 = std::make_unique <N[]>(1);
                node_tmp_0[0] = std::get<0>(*it);
                node_tmp_1[0] = std::get<1>(*it);
                node_.push_back(std::move(node_tmp_0));
                node_.push_back(std::move(node_tmp_1));
                auto edge_tmp = std::make_unique <std::tuple<N, N, E>[]>(1);
                edge_tmp[0] = *it;
                edge_.push_back(std::move(edge_tmp));
            }
            sort(); 
        }

    Graph<N, E>(typename std::initializer_list<N> source) noexcept {
        for (auto it = source.begin(); it != source.end(); ++it) {
            auto node_tmp = std::make_unique <N[]>(1);
                node_tmp[0] = *it;
                node_.push_back(std::move(node_tmp));
        }
    }

    //Copy Constructor
    Graph<N, E>(const gdwg::Graph<N, E>& source) noexcept {
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
        sort();
    }

    //Move Constructor
    Graph<N, E>(gdwg::Graph<N, E>&& source) noexcept : node_{std::move(source.node_)}, edge_{std::move(source.edge_)}{

    }

    //Destructor
    ~Graph<N, E>() = default;

//Operations
    //Copy Assignment
    Graph<N, E>& operator=(const gdwg::Graph<N, E>& rhs) noexcept {
        for (auto it = rhs.node_.begin(); it != rhs.node_.end(); ++it) {
            auto node_tmp = std::make_unique <N[]>(1);
            node_tmp[0] = (*it)[0];
            this->node_.push_back(std::move(node_tmp));
        }
        for (auto it = rhs.edge_.begin(); it != rhs.edge_.end(); ++it) {
            auto edge_tmp = std::make_unique <std::tuple<N, N, E>[]>(1);
            edge_tmp[0] = (*it)[0];
            this->edge_.push_back(std::move(edge_tmp));
        }
        this->sort();
        return *this;
    }

    //Move Assignment
    Graph<N, E>& operator=(gdwg::Graph<N, E>&& rhs) noexcept {
        this->node_ = std::move(rhs.node_);
        this->edge_ = std::move(rhs.edge_);
        this->sort();
        return *this;
    }

//Methods
    //InsertNode()
    bool InsertNode(const N& val) noexcept {
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (val == (*it)[0]) {
                return false;
            }
        }
        auto node_tmp = std::make_unique <N[]>(1);
        node_tmp[0] = val;
        this->node_.push_back(std::move(node_tmp)); 
        this->sort(); 
        return true;
    }

    //InsertEdge
    bool InsertEdge(const N& src, const N& dst, const E& w) {
        auto flag_1 = false;
        auto flag_2 = false;
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (src == (*it)[0]) {
                flag_1 = true;
            }
            if (dst == (*it)[0]) {
                flag_2 = true;
            }
        }
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ++it) {
            if (src == std::get<0>((*it)[0]) && dst == std::get<1>((*it)[0]) && w == std::get<2>((*it)[0])) {
                return false;
            }
        }
        if ((flag_1 || flag_2)== false) {
            throw std::runtime_error("Cannot call Graph::InsertEdge when either src or dst node does not exist");
        }
        auto edge_tmp = std::make_unique <std::tuple<N, N, E>[]>(1);
        edge_tmp[0] = std::make_tuple(src, dst, w);
        this->edge_.push_back(std::move(edge_tmp)); 
        this->sort(); 
        return true;      
    }

    //DeleteNode
    bool DeleteNode(const N& node_name) {
        auto flag = false;
        for (auto it = this->node_.begin(); it != this->node_.end(); ) {
            if (node_name == (*it)[0]) {
                flag = true;
                it = this->node_.erase(it);
            } else {
                ++it;
            }
        }
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ) {
            if (node_name == std::get<0>((*it)[0]) || node_name == std::get<1>((*it)[0])) {
                it = this->edge_.erase(it);
            } else {
                ++it;
            }       
        }
        return flag;
    }

    //MergeReplace
    bool MergeReplace(const N& oldData, const N& newData) {
        auto flag_1 = true;
        auto flag_2 = true;
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (oldData == (*it)[0]) {
                flag_1 = false;
            } else if (newData == (*it)[0]) {
                flag_2 = false;
            }
        }
        if (flag_1 || flag_2) {
            throw std::runtime_error("Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph");
        }
        for (auto it = this->node_.begin(); it != this->node_.end(); ) {
            if (oldData == (*it)[0]) {
                it = this->node_.erase(it);
            } else {
                ++it;
            }
        }
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ++it) {
            if (oldData == std::get<0>((*it)[0])) {
                std::get<0>((*it)[0]) = newData;
            } 
            else if (oldData == std::get<1>((*it)[0])) {
                std::get<1>((*it)[0]) = newData;
            }    
        }
        this->sort(); 
        return true;                
    }

    //Clear
    void Clear() {
        this->node_.clear();
        this->edge_.clear();
    }

    //IsNode
    bool IsNode(const N& val) {
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (val == (*it)[0]) {
               return true;
            } 
        }
        return false;
    }

    //IsConnected
    bool IsConnected(const N& src, const N& dst) {
        auto flag_1 = true;
        auto flag_2 = true;
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (src == (*it)[0]) {
                flag_1 = false;
            } else if (dst == (*it)[0]) {
                flag_2 = false;
            }
        }
        if (flag_1 || flag_2) {
            throw std::runtime_error("Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
        }
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ++it) {
            if (src == std::get<0>((*it)[0]) && dst == std::get<1>((*it)[0])) {
                return true;
            }
        }
        return false;
    }

    //GetNodes
    std::vector<N> GetNodes() {
        std::vector<N> result;
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            result.push_back((*it)[0]);
        }
        return result;
    }

    //GetConnected
    std::vector<N> GetConnected(const N& src) { 
        auto flag = true;
        std::vector<N> result;
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (src == (*it)[0]) {
                flag = false;
            }
        }
        if (flag == true) {
            throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
        }
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ++it) {
            if (src == std::get<0>((*it)[0]) && !std::count(result.begin(), result.end(), src)) {
                result.push_back(std::get<1>((*it)[0]));
            }
        }
        return result;
    }

    //GetWeights
    std::vector<E> GetWeights(const N& src, const N& dst) {
        auto flag_1 = true;
        auto flag_2 = true;
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (src == (*it)[0]) {
                flag_1 = false;
            } else if (dst == (*it)[0]) {
                flag_2 = false;
            }
        }
        if (flag_1 || flag_2) {
            throw std::out_of_range("Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
        }
        std::vector<E> result;
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ++it) {
            if (src == std::get<0>((*it)[0]) && dst == std::get<1>((*it)[0])) {
                result.push_back(std::get<2>((*it)[0]));
            }
        }
        return result;
    }

//Friends
    friend std::ostream& operator<<(std::ostream& os, const gdwg::Graph<N, E>& g){   
        for (auto it_n = g.node_.begin(); it_n != g.node_.end(); ++it_n) {
            os << (*it_n)[0] << "(\n"; 
            for (auto it_e = g.edge_.begin(); it_e != g.edge_.end(); ++it_e) {
                if ((*it_n)[0] == std::get<0>((*it_e)[0])) {
                    os << "  " << std::get<1>((*it_e)[0]) << " | " << std::get<2>((*it_e)[0]) << "\n";
                }
            }
            os << ")\n";
        }
        return os;
    }

    friend bool operator==(const gdwg::Graph<N, E>& lhs, const gdwg::Graph<N, E>& rhs) {
        auto it_r1 = rhs.node_.begin();
        for (auto it_l = lhs.node_.begin(); it_l != lhs.node_.end(); ++it_l) {
            std::cout << (*it_l)[0] << " and " << (*it_r1)[0]<<"\n" ;
            if ((*it_l)[0] != (*it_r1)[0]) {
                return false;
            }
            it_r1++;
        }
        auto it_r2 = rhs.edge_.begin();
        for (auto it_l = lhs.edge_.begin(); it_l != lhs.edge_.end(); ++it_l) {
            if (std::get<0>((*it_l)[0]) != std::get<0>((*it_r2)[0]) || std::get<1>((*it_l)[0]) != std::get<1>((*it_r2)[0]) || std::get<2>((*it_l)[0]) != std::get<2>((*it_r2)[0])) {
                return false;
            }
            it_r2++;
        }
        return true;
    }

    friend bool operator!=(const gdwg::Graph<N, E>& lhs, const gdwg::Graph<N, E>& rhs) {
        auto result = false;
        auto it_r1 = rhs.node_.begin();
        for (auto it_l = lhs.node_.begin(); it_l != lhs.node_.end(); ++it_l) {
            std::cout << (*it_l)[0] << " and " << (*it_r1)[0]<<"\n" ;
            if ((*it_l)[0] != (*it_r1)[0]) {
                result = true;
            }
            it_r1++;
        }
        auto it_r2 = rhs.edge_.begin();
        for (auto it_l = lhs.edge_.begin(); it_l != lhs.edge_.end(); ++it_l) {
            if (std::get<0>((*it_l)[0]) != std::get<0>((*it_r2)[0]) || std::get<1>((*it_l)[0]) != std::get<1>((*it_r2)[0]) || std::get<2>((*it_l)[0]) != std::get<2>((*it_r2)[0])) {
                result = true;
            }
            it_r2++;
        }
        return result;
    }

 private:
    std::vector <std::unique_ptr<N[]>> node_;
    std::vector <std::unique_ptr<std::tuple<N, N, E>[]>> edge_;

    void sort() {
        for (int i = node_.size() - 1; i > -1; i--) {
            for (int j = 0; j < i; j ++) {
                if (node_[j][0] > node_[j + 1][0]) {
                    std::swap(node_[j][0], node_[j + 1][0]);
                }
            }
        }
        auto it_n = node_.begin();
        while (it_n != node_.end() - 1) {
            if ((*it_n)[0] == (*(it_n + 1))[0]) {
                it_n = node_.erase(it_n);
            }
            else {
                ++it_n;
            }
        }

        if (edge_.size() > 0) {
            for (int i = edge_.size() - 1; i > -1; i--) {
                for (int j = 0; j < i; j ++) {
                    if (std::get<1>(edge_[j][0]) > std::get<1>(edge_[j + 1][0])) {
                        std::swap(edge_[j][0], edge_[j + 1][0]);
                    }
                    else if (std::get<1>(edge_[j][0]) == std::get<1>(edge_[j + 1][0]) && std::get<2>(edge_[j][0]) > std::get<2>(edge_[j + 1][0])) {
                        std::swap(edge_[j][0], edge_[j + 1][0]);
                    } 
                }
            }
            auto it_e = edge_.begin();
            while (it_e != edge_.end() - 1) {
                if ((*it_e)[0] == (*(it_e + 1))[0]) {
                    it_e = edge_.erase(it_e);
                }
                else {
                    ++it_e;
                }
            }
        }
    }
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
