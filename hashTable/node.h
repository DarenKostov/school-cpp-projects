/*
  Daren Kostov
  a Node class- the backbone of a linked list

  Note:
  you can make a linked list of multiple data types, just like arrays in JS!


  NOTE:
  T IS WHAT IS STORED IN THE NODE, DONT SET IT AS A POINTER,
  PUT WHAT YOU WILL STORE IN IT
  ..or you can spend hours trying to figure out why you give
  it an int pointer but it wants a int pointer pointer 

*/


template <class T>
class Node{
  public:
    //create a Node with a value
    Node(T*);
  
    //create a Node without a value
    Node();
    
    //destroy a Node | WARNING this will break your linked list, dont use it unless you know what youre doing, use the deleteMe() instead
    ~Node();
    
    //=getters
  
    //gives you the next Node in the linked list
    Node* getNext()const;
    
    //gives you the previous Node in the linked list
    Node* getPrev()const;
    Node* getPrevious()const;  

    //gives you the value stored in this Node;
    T* getValue()const;
    T* val()const;

    //=setters | WARNING these will break the linked list, dont use unless you know what you are doing, use the adders instead
    
    //sets the next Node
    void setNext(Node*);
    
    //sets the previous Node
    void setPrev(Node*);
  
    //sets the value
    void setValue(T*);
  
    //=adders
  
    //adds a Node after this Node, return the new TAIL if it was the TAIL, returns itself if not
    Node* addNext(Node*);
    Node* addForward(Node*);
    Node* addAfter(Node*);
  
    //adds a Node before this Node, returns the new HEAD if it was the HEAD, returns itself if not
    Node* addPrev(Node*);
    Node* addBackwards(Node*);
    Node* addBefore(Node*);
    Node* addPrevious(Node*);
  
    //=deleters
    
    //deletes this Node | returns the new HEAD if it was the HEAD, returns the new TAIL if it was the TAIL, returns nullptr if it was neither or both
    Node* removeMe();
    Node* deleteMe();


    //detaches the node from the other nodes, returns nothing
    void detachMe();

    
    private:
    //what is the next Node?
    Node* next;
    //what is the previous Node?
    Node* previous;
    //what are we storing?
    T* value;
};

#include "./node.tpp"

