/*-------------------------------------------
 Project 5 - OpenStreetMap
 have implemented a graph
 have implemented a fundamental graph algorithm
 have a working maps application that can find paths in real data

 
Course: CS 251, Spring 2024, UIC
System: xcode
Author: Manav Malik
------------------------------------------- */
#include "application.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iomanip> /*setprecision*/
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "dist.h"
#include "graph.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

double INF = numeric_limits<double>::max();

graph<long long, double> buildGraph(
    const map<long long, Coordinates>& Nodes,
    const vector<FootwayInfo>& Footways,
    const vector<BuildingInfo>& Buildings) {
    graph<long long, double> G;

    // TODO_STUDENT
    
    //vertices
    for(auto it = Nodes.begin() ; it!=Nodes.end() ; it++ ){
        G.addVertex(it->first);
    }
    
    //ediges
    for (int i=0; i<Footways.size() ; i++){
        vector<long long> the_footway = Footways[i].Nodes;
        
        for (int j=1 ; j<the_footway.size() ; j++){
            
            long long id1 = the_footway[j-1];
            long long id2 = the_footway[j];
            
            Coordinates c1 = Nodes.at(id1);
            Coordinates c2 = Nodes.at(id2);
            
            double the_distence = distBetween2Points( c1.Lat,  c1.Lon,  c2.Lat,  c2.Lon);
            
            G.addEdge(id1, id2, the_distence);
            G.addEdge(id2, id1, the_distence);
            
        }
    }
    
    
    //buildings
    for (int k=0; k<Buildings.size() ; k++){
        
        BuildingInfo the_building = Buildings[k];
        
        G.addVertex(the_building.Coords.ID);
        
        //Coordinates nearest ;
        for(auto it = Nodes.begin() ; it!=Nodes.end() ; it++ ){
            if (it->second.OnFootway == true){
                double dist =distBetween2Points( the_building.Coords.Lat,  the_building.Coords.Lon,  it->second.Lat,  it->second.Lon);
                if (dist <= 0.041){
                    Coordinates nearest = it->second;
                    
                    
                    G.addEdge(it->first, the_building.Coords.ID, dist);
                    G.addEdge(the_building.Coords.ID, it->first, dist);
                    
                    //break;
                }
            }
        }
    }

    return G;
}



// start by making the p.que
// start node value to 0

// an map to keep track of all the node not visited yet so that me can compere the length till noe to the previous length

// the while loop till the empty of p.que
// or time to deque the end node from p.que (when we deque and get the end)

// should not include   "ignoreNodes"
//should not include checked and completed node

//If the target is unreachable from start, just return an empty path.
// If start and target are the same, return a vector containing just start.


class prioritize {
   public:
    bool operator()(const tuple<long long, double,vector<long long> >& p1,
                    const tuple<long long, double,vector<long long> >& p2) const {
        return get<1>(p1) > get<1>(p2);
    }
};



vector<long long> dijkstra(
                           
    const graph<long long, double>& G,
                           
    long long start,  //from
    long long target,  // to
                           
    const set<long long>& ignoreNodes  //somthong
                           
                           ) {
    
    vector<long long> path;
    
    if (start == target){   //are you that stupid??
        path.push_back(start);
        return path;
    }
    
    // TODO_STUDENT
    
 priority_queue< tuple<long long, double,vector<long long>>, vector<tuple<long long, double,vector<long long>>>, prioritize > worklist;

                               
    auto the_bigning = make_tuple(start, 0 ,vector<long long>() );
    worklist.push(the_bigning);
                               
    set<long long> done;
    map<long long , double> unvisited;
                               
                               
                               
   vector<long long> nodes = G.getVertices();
   for (auto node : nodes) {
       unvisited[node] = INF;
   }
   unvisited[start] = 0;

    
    while(!worklist.empty()){
        
        // use top to get the element and pop to remove it
        tuple<long long, double,vector<long long>> the_current = worklist.top();
        worklist.pop();
        
        // getting the path till now and adding the curr to top;
        vector<long long> the_path = get<2>(the_current);
        long long the_cur_node = get<0>(the_current);
        double the_wight_tillnow = get<1>(the_current);
        
        unvisited.erase(the_cur_node);
        
        the_path.push_back( the_cur_node );
        if (the_cur_node == target){
            return the_path;
        }
                
        done.insert(the_cur_node);
        
        map<long long , double> the_nabours = G.neighbor_map(the_cur_node);
        
        for (auto itt = the_nabours.begin() ; itt!=the_nabours.end() ; itt++ ){
             
            long long nabour_id = itt->first;
            double nabour_wight = itt->second;
            
            if (nabour_id == target && done.find(nabour_id) == done.end() ){
                double sum = the_wight_tillnow+nabour_wight;
                
                if (sum < unvisited[nabour_id] ){
                    unvisited[nabour_id] = sum;
                    auto curr_nabour = make_tuple(nabour_id, sum , the_path);
                    worklist.push(curr_nabour);
                }
            }
            
            if (ignoreNodes.find(nabour_id) == ignoreNodes.end() && done.find(nabour_id) == done.end() ){
                
                double sum = the_wight_tillnow+nabour_wight;
                
                if (sum < unvisited[nabour_id] ){
                    unvisited[nabour_id] = sum;
                    auto curr_nabour = make_tuple(nabour_id, sum , the_path);
                    worklist.push(curr_nabour);
                }
                
            }
  
        }

    }
                       
    return path;
}











double pathLength(const graph<long long, double>& G, const vector<long long>& path) {
    double length = 0.0;
    double weight;
    for (size_t i = 0; i + 1 < path.size(); i++) {
        bool res = G.getWeight(path.at(i), path.at(i + 1), weight);
        assert(res);
        length += weight;
    }
    return length;
}

void outputPath(const vector<long long>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << path.at(i);
        if (i != path.size() - 1) {
            cout << "->";
        }
    }
    cout << endl;
}

void application(
    const vector<BuildingInfo>& Buildings,
    const graph<long long, double>& G) {
    string person1Building, person2Building;

    set<long long> buildingNodes;
    for (const auto& building : Buildings) {
        buildingNodes.insert(building.Coords.ID);
    }

    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);

    while (person1Building != "#") {
        cout << "Enter person 2's building (partial name or abbreviation)> ";
        getline(cin, person2Building);

        //
        // find the building coordinates
        //
        bool foundP1 = false;
        bool foundP2 = false;
        Coordinates P1Coords, P2Coords;
        string P1Name, P2Name;

        for (const BuildingInfo& building : Buildings) {
            if (building.Abbrev == person1Building) {
                foundP1 = true;
                P1Name = building.Fullname;
                P1Coords = building.Coords;
            }
            if (building.Abbrev == person2Building) {
                foundP2 = true;
                P2Name = building.Fullname;
                P2Coords = building.Coords;
            }
        }

        for (const BuildingInfo& building : Buildings) {
            if (!foundP1 &&
                building.Fullname.find(person1Building) != string::npos) {
                foundP1 = true;
                P1Name = building.Fullname;
                P1Coords = building.Coords;
            }
            if (!foundP2 && building.Fullname.find(person2Building) != string::npos) {
                foundP2 = true;
                P2Name = building.Fullname;
                P2Coords = building.Coords;
            }
        }

        if (!foundP1) {
            cout << "Person 1's building not found" << endl;
        } else if (!foundP2) {
            cout << "Person 2's building not found" << endl;
        } else {
            cout << endl;
            cout << "Person 1's point:" << endl;
            cout << " " << P1Name << endl;
            cout << " (" << P1Coords.Lat << ", " << P1Coords.Lon << ")" << endl;
            cout << "Person 2's point:" << endl;
            cout << " " << P2Name << endl;
            cout << " (" << P2Coords.Lat << ", " << P2Coords.Lon << ")" << endl;

            string destName;
            Coordinates destCoords;

            Coordinates centerCoords = centerBetween2Points(
                P1Coords.Lat, P1Coords.Lon, P2Coords.Lat, P2Coords.Lon);

            double minDestDist = numeric_limits<double>::max();

            for (const BuildingInfo& building : Buildings) {
                double dist = distBetween2Points(
                    centerCoords.Lat, centerCoords.Lon,
                    building.Coords.Lat, building.Coords.Lon);
                if (dist < minDestDist) {
                    minDestDist = dist;
                    destCoords = building.Coords;
                    destName = building.Fullname;
                }
            }

            cout << "Destination Building:" << endl;
            cout << " " << destName << endl;
            cout << " (" << destCoords.Lat << ", " << destCoords.Lon << ")" << endl;

            vector<long long> P1Path = dijkstra(G, P1Coords.ID, destCoords.ID, buildingNodes);
            vector<long long> P2Path = dijkstra(G, P2Coords.ID, destCoords.ID, buildingNodes);

            // This should NEVER happen with how the graph is built
            if (P1Path.empty() || P2Path.empty()) {
                cout << endl;
                cout << "At least one person was unable to reach the destination building. Is an edge missing?" << endl;
                cout << endl;
            } else {
                cout << endl;
                cout << "Person 1's distance to dest: " << pathLength(G, P1Path);
                cout << " miles" << endl;
                cout << "Path: ";
                outputPath(P1Path);
                cout << endl;
                cout << "Person 2's distance to dest: " << pathLength(G, P2Path);
                cout << " miles" << endl;
                cout << "Path: ";
                outputPath(P2Path);
            }
        }

        //
        // another navigation?
        //
        cout << endl;
        cout << "Enter person 1's building (partial name or abbreviation), or #> ";
        getline(cin, person1Building);
    }
}
