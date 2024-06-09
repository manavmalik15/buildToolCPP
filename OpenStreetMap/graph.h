/*-------------------------------------------
 Project 5 - OpenStreetMap
 have implemented a graph
 have implemented a fundamental graph algorithm
 have a working maps application that can find paths in real data

 
Course: CS 251, Spring 2024, UIC
System: xcode
 Author: Manav Malik
 ------------------------------------------- */
#pragma once

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

/// @brief Simple directed graph using an adjacency list.
/// @tparam VertexT vertex type
/// @tparam WeightT edge weight type
template <typename VertexT, typename WeightT>
class graph {
   private:
    // TODO_STUDENT
    map< VertexT , map< VertexT , WeightT> > the_graph ;
    
   public:
    /// Default constructor
//    graph() {
//        // TODO_STUDENT
//    }
// the cpp  alrady has a diffalt constructor so this would not be needed

    
    
    
    

//     mymap['a']=50;
//     mymap['b']=100;
//
//     auto it = mymap.find('b');
//     if (it != mymap.end())
//       mymap.erase (it);
//
//     std::cout << "elements in mymap:" << '\n';
//     std::cout << "a => " << mymap.find('a')->second << '\n';
//     std::cout << "c => " << mymap.find('c')->second << '\n';
    
    
    
    /// @brief Add the vertex `v` to the graph, must run in at most O(log |V|).
    /// @param v ..
    /// @return true if successfully added; false if it existed already
    bool addVertex(VertexT v) {
        // TODO_STUDENT
        auto res = the_graph.emplace(v, map<VertexT, WeightT>());
        return res.second;
        
    }

    /// @brief Add or overwrite directed edge in the graph, must run in at most O(log |V|).
    /// @param from starting vertex
    /// @param to ending vertex
    /// @param weight edge weight / label
    /// @return true if successfully added or overwritten;
    ///         false if either vertices isn't in graph
    bool addEdge(VertexT from, VertexT to, WeightT weight) {
        // TODO_STUDENT
        
        if (the_graph.find(from) == the_graph.end() || the_graph.find(to) == the_graph.end() ){
            return false;
        }
        
        the_graph[from][to]=weight;
        
        return true;
    }

    /// @brief Maybe get the weight associated with a given edge, must run in at most O(log |V|).
    /// @param from starting vertex
    /// @param to ending vertex
    /// @param weight output parameter
    /// @return true if the edge exists, and `weight` is set;
    ///         false if the edge does not exist
    bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
        // TODO_STUDENT
        
        auto the_vertex = the_graph.find(from);
        if (the_vertex != the_graph.end() ){
            
            auto the_edges = the_vertex->second.find(to) ;
            
            if (the_edges != the_vertex->second.end() ){
                
                weight = the_edges->second;
                return true;
            }
        }
        
//        weight = the_graph[from][to] ;
        
        return false;
    }
    


    /// @brief Get the out-neighbors of `v`. Must run in at most O(|V|).
    /// @param v  ..
    /// @return vertices that v has an edge to
    set<VertexT> neighbors(VertexT v) const {
        set<VertexT> S;
        
        auto the_point = the_graph.find(v);
        
        if (the_point != the_graph.end()) {
            
            for (auto it = the_point->second.begin(); it != the_point->second.end(); ++it) {
                S.insert(it->first);
            }
        }
        
        return S;
    }

    /// @brief Return a vector containing all vertices in the graph
    vector<VertexT> getVertices() const {
        // TODO_STUDENT
//        return vector<VertexT>{};
        vector<VertexT> s;
        for(auto it = the_graph.begin() ; it!=the_graph.end() ; it++ ){
            s.push_back(it->first);
        }
        return s;
    }

    /// @brief Get the number of vertices in the graph. Runs in O(1).
    size_t NumVertices() const {

        return the_graph.size();
    }

    /// @brief Get the number of directed edges in the graph. Runs in at most O(|V|).
    size_t NumEdges() const {
        // TODO_STUDENT
        
        
        size_t sum=0;
        
        for(auto it = the_graph.begin() ; it!=the_graph.end() ; it++ ){
            sum= sum + it->second.size();
        }
        
        return sum;
    }
    
    
    
    
    map<VertexT, WeightT> neighbor_map(VertexT v) const {
            auto it = the_graph.find(v);
            if (it != the_graph.end()) {
                return it->second; 
            }
            return map<VertexT, WeightT>();
        }
    
    
    
    
    
    
    
    
};
