//
// Created by Tobin Joseph on 11/12/20.
//

#ifndef PROJECT3_PRIORITYQUEUE_H
#define PROJECT3_PRIORITYQUEUE_H

#include <vector>
#include <utility>
#include "json.hpp"
typedef double                  Key;
typedef std::pair<int, int>     Value;
typedef std::pair<Key, Value>   KeyValuePair;

class PriorityQueue {
public:
    PriorityQueue(std::size_t max_nodes);
    void insert(Key k);
    void insert(KeyValuePair kv);
    KeyValuePair min();
    KeyValuePair removeMin();
    bool isEmpty() const;
    size_t size() const;
    nlohmann::json JSON() const;
   // void removeNode(size_t i);
    void printPriorityQueue (std::ostream& out) const;

private:
    void heapifyUp(size_t i);
    void heapifyDown(size_t i);
    void removeNode(size_t i);
    Key getKey(size_t i);

    std::vector<KeyValuePair>   nodes_;
    size_t                      max_size_;
    size_t                      size_;

    const static size_t         ROOT = 1;

};  // class PriorityQueue


#endif //PROJECT3_PRIORITYQUEUE_H
