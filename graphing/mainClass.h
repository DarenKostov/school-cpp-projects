/*
  Daren Kostov

  a class that contains the main startup and loop

  it's not called just "Main" because "main" is too close to it
  
*/

#include "text.h"
#include <unordered_map>
#include <set>
#include <stack>
#include <vector>

class MainClass{

  private:
    //variables:

    std::set<Text*> nodes;
    std::unordered_map<Text*, std::unordered_map<Text*, unsigned int>> links;
    
    
  public:

    //constructor, like a atSTartUp function
    MainClass();

    //deconstror
    ~MainClass();

    //the function that does all the logic, basically the main function
    void startProgram();



    //adds a node
    void addNodeCommand(std::vector<Text>);

    //adds a link
    void addLinkCommand(std::vector<Text>);

    //removes a node
    void removeNodeCommand(std::vector<Text>);

    //removes a link
    void removeLinkCommand(std::vector<Text>);


    //prints the adjacency table
    void printLinks();
    
    //tells you the shortest path between 2 nodes
    void getShortestPath(std::vector<Text>);
  
    //internal functions for operations
  private:

    //gives you node with the label given, if it doesnt exist it return nullptr
    Text* getNodeWithName(Text);
  
    //adds a node
    void addNode(Text*);

    //removes a node
    void removeNode(Text*);

    //connects 2 nodes
    void addLink(Text*, Text*, int);
    
    //disconnects 2 nodes
    void removeLink(Text*, Text*);

    //print's stuff about a node
    void probe(Text);
    
    int findShortestPath(std::stack<Text*>&, Text*, Text*);
};
