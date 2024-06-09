#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>

#include "tinyxml2.h"
#include "graph.h"
#include "osm.h"
#include "application.h"

using namespace std;
using namespace tinyxml2;

//
//int main() {
//  // maps a Node ID to it's coordinates (lat, lon)
//  map<long long, Coordinates>  Nodes;
//  // info about each footway, in no particular order
//  vector<FootwayInfo>          Footways;
//  // info about each building, in no particular order
//  vector<BuildingInfo>         Buildings;
//  XMLDocument                  xmldoc;
//
//  cout << "** Navigating UIC open street map **" << endl;
//  // cout << endl;
//  cout << setprecision(8);
//
//  string default_filename = "uic-2024.osm";
//  string filename;
//
//  // cout << "Enter map filename> ";
//  // getline(cin, filename);
//
//  if (filename == "") {
//    filename = default_filename;
//  }
//
//  // Load XML-based map file
//  if (!LoadOpenStreetMap(filename, xmldoc)) {
//    cout << "**Error: unable to load open street map." << endl;
//    cout << endl;
//    return 0;
//  }
//
//  // Read the nodes, which are the various known positions on the map:
//  int nodeCount = ReadMapNodes(xmldoc, Nodes);
//
//  // Read the footways, which are the walking paths:
//  int footwayCount = ReadFootways(xmldoc, Nodes, Footways);
//
//  // Read the university buildings:
//  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);
//
//  // Stats
//  assert(nodeCount == (int)Nodes.size());
//  assert(footwayCount == (int)Footways.size());
//  assert(buildingCount == (int)Buildings.size());
//
//  // cout << endl;
//  cout << "# of nodes: " << Nodes.size() << endl;
//  cout << "# of footways: " << Footways.size() << endl;
//  cout << "# of buildings: " << Buildings.size() << endl;
//
//  // Build graph from input data
//  graph<long long, double> G = buildGraph(Nodes, Footways, Buildings);
//
//  // More stats
//  cout << "# of vertices: " << G.NumVertices() << endl;
//  cout << "# of edges: " << G.NumEdges() << endl;
//  application(Buildings, G);
//
//  cout << "** Done **" << endl;
//  return 0;
//}








int main(){
    
    graph<string, int> g;  // Create a graph with string vertices and int weights

        // Add some vertices
        cout << "Adding vertices...\n";
        cout << "Added 'A': " << g.addVertex("A") << endl;
        cout << "Added 'B': " << g.addVertex("B") << endl;
        cout << "Added 'C': " << g.addVertex("C") << endl;
        cout << "Added 'D': " << g.addVertex("D") << endl;
        cout << "Added 'E': " << g.addVertex("E") << endl;

        // Add some edges
        cout << "\nAdding edges...\n";
        if (g.addEdge("A", "B", 1)) {
            cout << "Edge A -> B with weight 1 added.\n";
        } else {
            cout << "Failed to add edge A -> B. Check if both vertices exist.\n";
        }
        g.addEdge("A", "C", 2);
        g.addEdge("B", "B", 3);
        g.addEdge("C", "A", 4);
        g.addEdge("D", "E", 5);
        g.addEdge("E", "A", 6);

    
    
    vector<string> the_ver = g.getVertices();
    
    cout<<"the list of verteces \n";
    for (int i =0 ;i<the_ver.size() ; i++){
        cout<<"the vertex at "<<i<<" is "<<the_ver[i]<<endl;
        
        set<string> the_edg = g.neighbors(the_ver[i]);
        
//        for (int j =0 ;j<the_edg.size() ; j++){
//            cout<<"      the edg from this to "<<the_edg.at<<endl;
//            
//        } 
    }
    
    return 0;
}
