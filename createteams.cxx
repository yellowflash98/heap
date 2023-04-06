//
// Created by Tobin Joseph on 11/12/20.
//


#include <iostream>

#include "json.hpp"
#include "priorityqueue.h"
#include<fstream>
#include <vector>
#include <set>
using namespace std;
/*
std::ostream& operator<< (std::ostream& out, const PriorityQueue& pq)
{
    pq.printPriorityQueue(out);
    return out;
}
*/

int main(int argc, char** argv) {
    std::ifstream inputFile;
    //inputFile.open("TestCase1.buildheap.json");
    inputFile.open(argv[1]);
    nlohmann::json jsonObjectInput;
    if (inputFile.is_open()) {
        inputFile >> jsonObjectInput;
        //cout <<jsonObjectInput.dump(2) << "\n";
    }
    PriorityQueue pq = PriorityQueue(((size_t)(jsonObjectInput["teamStats"].size())));
    //cout<<jsonObjectInput["teamStats"].size();
    nlohmann::json teamStatsArray = jsonObjectInput["teamStats"];
    nlohmann::json twoPlayerTeamStat;
    double key;
    int player1;
    int player2;

    for (auto arrayItr = teamStatsArray.begin();
         arrayItr  != teamStatsArray.end();
         ++arrayItr ) {
        twoPlayerTeamStat=*arrayItr;
        //cout <<twoPlayerTeamStat.dump(2) << "\n";
        key=fabs(50.00-(double)(twoPlayerTeamStat["winPercentage"]));
        player1=twoPlayerTeamStat["playerOne"];
        player2=twoPlayerTeamStat["playerTwo"];
       // std::make_pair(key, make_pair(player1, player2)));
        pq.insert(make_pair(key, make_pair(player1, player2)));
    }
    set<int> playersSet;
    vector<KeyValuePair> finalTeams;

    while(pq.size()!=0) {
        KeyValuePair kvp = pq.min();
        auto pos1 = playersSet.find(kvp.second.first);
        auto pos2=playersSet.find(kvp.second.second);
        if(*pos1==kvp.second.first || *pos2==kvp.second.second)
            pq.removeMin();
        else {

            finalTeams.push_back(kvp);

            playersSet.insert(kvp.second.first);
            playersSet.insert(kvp.second.second);
            //cout << "player1 = " << kvp.second.first << endl;
            //cout << "player2 = " << kvp.second.second << endl;
            pq.removeMin();
        }


    }
    nlohmann::json finalTeamsArray = nlohmann::json::array();
    for ( unsigned int i=0; i<finalTeams.size(); i++){
        //cout << "index = " << i<< " ";
        //cout << "key ="<< finalTeams.at(i).first<<" ";
        //cout << "value pair =" << finalTeams.at(i).second.first <<  ",";
        //cout << finalTeams.at(i).second.second;
        //cout<<endl;
       // nlohmann::json jsonOutput;
        nlohmann::json teamArray = nlohmann::json::array();
        teamArray.push_back(finalTeams.at(i).second.first);
        teamArray.push_back(finalTeams.at(i).second.second);
        finalTeamsArray.push_back(teamArray);


    }
    nlohmann::json jsonOutput =  nlohmann::json::object();
    //cout<<jsonOutput.empty()<<endl;
    //nlohmann::json jsonOutput=jsonOutput.erase();
    //jsonOutput.keySet().clear();
    //cout <<jsonOutput.dump(2) << "\n";
    //nlohmann::json jsonOutput;
   // jsonOutput.erase(jsonOutput.begin());
    jsonOutput["teams"]=finalTeamsArray;

    //cout <<jsonOutput.dump(2) << "\n";
    //nlohmann::json jsonOutput2=jsonOutput["teams"];
    cout <<jsonOutput.dump(2) << "\n";

}
