/*
  Daren Kostov
  a Node class- the backbone of a linked list

  Note:
  you can make a linked list of multiple data types, just like arrays in JS!


*/


template <class T>
class Node{
  public:
    //create a Node with a value
    Node(T*);
    
    //destroy a Node | WARNING this will break your linked list, dont use it unless you know what youre doing, use the deleteMe() instead
    ~Node();
    
    //=getters
  
    //gives you the next Node in the linked list
    Node* getNext()const;
    
    //gives you the previous Node in the linked list
    Node* getPrev()const;
    Node* getPrevious()const;  

    //gives you the value stored i this Node;
    T* getValue()const;
    T* val()const;

    //=setters | WARNING these will break the linked list, dont use unless you know what you are doing, use the adders instead
    
    //sets the next Node
    void setNext(Node*);
    
    //sets the previous Node
    void setPrev(Node*);
  
    //=adders
  
    //adds a Node after this Node, returns true for success
    void addNext(Node*);
    void addForward(Node*);
    void addAfter(Node*);
  
    //adds a Node before this Node, returns true for success
    void addPrev(Node*);
    void addBackwards(Node*);
    void addBefore(Node*);
    void addPrevious(Node*);
  
    //=deleters
    
    //deletes this Node | returns the new HEAD if it was the HEAD, returns the new TAIL if it was the TAIL, returns nullptr if it was neither or both
    Node* removeMe();
    Node* deleteMe();
    
    private:
    //what is the next Node?
    Node* next;
    //what is the previous Node?
    Node* previous;
    //what are we storing?
    T* value;
};


#include "./node.tpp"
