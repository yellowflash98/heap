#include <iostream>
#include <vector>
#include <utility>

#include "json.hpp"
#include "priorityqueue.h"
using namespace std;
PriorityQueue::PriorityQueue(std::size_t max_size) :
        nodes_(max_size + 1, KeyValuePair()),
        max_size_(max_size),
        size_(0) {
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    // TODO: complete this function
    //if queue is full then you cannot insert
   // cout<<"SIZE OF ARRAY before insertion ="<<size()<<endl;
    if(size()>max_size_)
        return;
    // a KeyValuePair always insert at the end of the array
    nodes_[size() +ROOT]=kv;
    heapifyUp(size() +ROOT);
    // increment the size by 1
    size_=size_+1;

}
//The  1st node has the minimum Key in the heap since we are writing a minimum priority queue.

KeyValuePair PriorityQueue::min() {
    return nodes_[ROOT];
}

KeyValuePair PriorityQueue::removeMin() {
    // TODO: complete this function
    //cout<<"SIZE OF ARRAY before removeMin ="<<size()<<endl;
    KeyValuePair tempKeyValuePair=nodes_[ROOT];
    if(isEmpty())
        return nodes_[ROOT];
    //Replace the value of root node with value of last element in the array
    nodes_[ROOT]=nodes_[size()];
   // cout<<"node_ROOT ="<< nodes_[ROOT].first<<endl;
    heapifyDown(ROOT);
    //replace the value of the last element by 0
    nodes_[size()]=std::make_pair(0.0, std::make_pair(0, 0));
    size_=size_ - 1;
    return tempKeyValuePair;
}

bool PriorityQueue::isEmpty() const {
    // TODO: complete this function
    if(size_ == 0)
        return true;
    else
        return false;
}

size_t PriorityQueue::size() const {
    // TODO: complete this function
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;
    for (size_t i = 1; i <= size_; i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    // TODO: complete this function
    size_t parentIndex = i;
    KeyValuePair tempKeyValuePair;

    while (parentIndex > ROOT) {
        parentIndex = i / 2; //parent index of i
        if (getKey(i) < getKey(parentIndex)) {// comparing parent key with i node key
            tempKeyValuePair = nodes_[i]; // swapping parent and child node
            nodes_[i] = nodes_[parentIndex];
            nodes_[parentIndex] = tempKeyValuePair;
            i = parentIndex;
        } else {
            break;
        }
    }
}


void PriorityQueue::heapifyDown(size_t i) {
    // TODO: complete this function
    //Indexes of the children of the ith node
    size_t leftChildIndex;
    size_t rightChildIndex;
    KeyValuePair tempKeyValuePair;
    //does ith node has any child node?
    while (2 * i <= (size() )) {
        leftChildIndex = 2 * i;        // left  child of ith node
        rightChildIndex = 2 * i + 1;    // right child of ith node
        // does ith node have 2 children
        if (rightChildIndex <= (size() )) {
            if (getKey(i) < getKey(leftChildIndex) && getKey(i) < getKey(rightChildIndex))
                break;
                // swap ith node with its smallest children node
            else {
                if (getKey(leftChildIndex) < getKey(rightChildIndex)) {
                    tempKeyValuePair = nodes_[i]; // swapping parent and child node
                    nodes_[i] = nodes_[leftChildIndex];
                    nodes_[leftChildIndex] = tempKeyValuePair;
                    i = leftChildIndex;
                } else {
                    tempKeyValuePair = nodes_[i]; // swapping parent and child node
                    nodes_[i] = nodes_[rightChildIndex];
                    nodes_[rightChildIndex] = tempKeyValuePair;
                    i = rightChildIndex;
                }
            }
        }
        // ith node has a left child node
        else {
            if (getKey(i) < getKey(leftChildIndex))
                break;
            else {
                tempKeyValuePair = nodes_[i]; // swapping parent and child node
                nodes_[i] = nodes_[leftChildIndex];
                nodes_[leftChildIndex] = tempKeyValuePair;
                i = leftChildIndex;
            }
        }
    }
}
void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function
    // nodes_.erase(nodes_.begin()+i);
    size_t parentIndex;
    KeyValuePair tempKeyValuePair;
    tempKeyValuePair=nodes_[i];
    nodes_[i]=nodes_[size()];
    size_=size_-1;
    parentIndex=i/2;

    if(i==ROOT || getKey(parentIndex)<getKey(i))
        heapifyDown(i);
    else
        heapifyUp(i);




}

Key PriorityQueue::getKey(size_t i) {
    // TODO: complete this function
    return nodes_[i].first;
}

void PriorityQueue::printPriorityQueue (std::ostream& out) const{
    out << "max size =" << max_size_ << "\n";
    out << " size =" << size_ << "\n";
    out << "root =" << ROOT << "\n";
    cout<<endl;
    for(int i=0; i<nodes_.size(); i++){
        out << "index = " << i<< " ";
        out << "key ="<< nodes_.at(i).first<<" ";
        out << "value pair =" << nodes_.at(i).second.first <<  ",";
        out << nodes_.at(i).second.second;
        out<<endl;
    }

}
