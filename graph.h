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

namespace std {
    template<class T> struct _Unique_if {
        typedef unique_ptr<T> _Single_object;
    };

    template<class T> struct _Unique_if<T[]> {
        typedef unique_ptr<T[]> _Unknown_bound;
    };

    template<class T, size_t N> struct _Unique_if<T[N]> {
        typedef void _Known_bound;
    };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args&&... args) {
            return unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
            typedef typename remove_extent<T>::type U;
            return unique_ptr<T>(new U[n]());
        }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args&&...) = delete;
}

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
	class const_iterator {
	 	public:
	 		using value_type = std::tuple<N, N, E>;
	 		// using reference = std::tuple<const N&, const N&, const E& >;
	 		// iterator constructor
	 		const_iterator(typename std::vector <std::unique_ptr<std::tuple<N, N, E>[]>>::iterator x) {
	 			current = x;
			 }
			bool operator != (const const_iterator & rhs) {
				return this->current != rhs.current;
			}
			bool operator == (const const_iterator & rhs) {
				return this->current == rhs.current;
			}
			// prefix increment
			const_iterator& operator++ () {
				current++;
				return *this;
			}
			//postfix increment
			const_iterator& operator++ (int unused) {
				current++;
				return *this;
			}
			typename std::unique_ptr<std::tuple<N, N, E>[]>& operator*() {
				return *current;
			}
	 	
	 	private:
	 		typename std::vector <std::unique_ptr<std::tuple<N, N, E>[]>>::iterator current; 
	 	
	 }; 
//Constructors & Destructors

    //Default Constructor
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

    //Copy Constructor
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

    //Move Constructor
    Graph<N, E>(gdwg::Graph<N, E>&& source) : node_{std::move(source.node_)}, edge_{std::move(source.edge_)}{

    }

    //Destructor
    ~Graph<N, E>() = default;

//Operations
    //Copy Assignment
    Graph<N, E>& operator=(const gdwg::Graph<N, E>& rhs) {
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
        return *this;
    }

    //Move Assignment
    Graph<N, E>& operator=(gdwg::Graph<N, E>&& rhs) {
        this->node_ = std::move(rhs.node_);
        this->edge_ = std::move(rhs.edge_);
        return *this;
    }

//Methods
    //InsertNode()
    bool InsertNode(const N& val) {
        for (auto it = this->node_.begin(); it != this->node_.end(); ++it) {
            if (val == (*it)[0]) {
                return false;
            }
        }
        auto node_tmp = std::make_unique <N[]>(1);
        node_tmp[0] = val;
        this->node_.push_back(std::move(node_tmp)); 
        return true;
    }

    //InsertEdge
    bool InsertEdge(const N& src, const N& dst, const E& w) {
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ++it) {
            if (src == std::get<0>((*it)[0]) && dst == std::get<1>((*it)[0]) && w == std::get<2>((*it)[0])) {
                return false;
            }
        }
        auto edge_tmp = std::make_unique <std::tuple<N, N, E>[]>(1);
        edge_tmp[0] = std::make_tuple(src, dst, w);
        this->edge_.push_back(std::move(edge_tmp));  
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
        auto flag = true;
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
        return flag;                
    }

    //Clear
    void Clear() {
        this->node_.clear();
        this->edge_.clear();
    }

    //IsNode
    bool IsNode(const N& val) {
        for (auto it = this->node_.begin(); it != this->node_.end(); ) {
            if (val == (*it)[0]) {
               return true;
            } 
        }
        return false;
    }

    //IsConnected
    bool IsConnected(const N& src, const N& dst) {
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

    //GetWeights
    std::vector<E> GetWeights(const N& src, const N& dst) {
        std::vector<N> result;
        for (auto it = this->edge_.begin(); it != this->edge_.end(); ++it) {
            if (src == std::get<0>((*it)[0]) && dst == std::get<1>((*it)[0])) {
                result.push_back(std::get<2>((*it)[0]));
            }
        }
        return false;
    }
    // begin()
    const_iterator begin() {
    	return const_iterator(edge_.begin());
	}
	const_iterator end() {
    	return const_iterator(edge_.end());
	}
	
//Friends
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



#endif  // ASSIGNMENTS_DG_GRAPH_H_
