//
// Created by Tobin Joseph on 11/12/20.
//
#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"
#include<fstream>
using namespace std;
int main(int argc, char** argv) {
    std::ifstream inputFile;
    //inputFile.open("TestCase1.buildheap.json");
    inputFile.open(argv[1]);
    nlohmann::json jsonObjectInput;
    if (inputFile.is_open()) {
        inputFile >> jsonObjectInput;

    }
    PriorityQueue pq = PriorityQueue((size_t)(jsonObjectInput["metadata"]["maxHeapSize"]));
    for (auto itr = jsonObjectInput.begin(); itr != jsonObjectInput.end(); ++itr) {
        if(itr.key() != "metadata"){
            if(itr.value()["operation"]=="insert")
                pq.insert((size_t)(itr.value()["key"]));
            else if (itr.value()["operation"]=="removeMin")
                pq.removeMin();
            else cout<<"invalid operation"<<endl;


        }
    }
    nlohmann::json jsonOutput=pq.JSON();
    jsonOutput["metadata"]["maxHeapSize"]=jsonObjectInput["metadata"]["maxHeapSize"];
    jsonOutput["metadata"]["numOperations"]=jsonObjectInput["metadata"]["numOperations"];
    cout <<jsonOutput.dump(2) << "\n";
}