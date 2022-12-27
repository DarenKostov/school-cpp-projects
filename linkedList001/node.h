/*
  Daren Kostov
  a Node class- the backbone of a linked list
*/


template <class T>
class Node{
  public:
    //create a Node with a value
    Node(T*);
    
    //destroy a Node
    ~Node();
    
    //=getters
  
    //gives you the next Node in the linked list
    Node* getNext();
    
    //gives you the previous Node in the linked list
    Node* getPrevious();  
    Node* getPrev();

    //gives you the value stored i this Node;
    T* getValue();
    T* val();

    //=setters
    
    //adds a Node after this Node
    bool addForward(Node*);
    bool addAfter(Node*);
    bool addNext(Node*);
  
    //adds a Node before this Node
    bool addBackwards(Node*);
    bool addBefore(Node*);
    bool addPrevious(Node*);
    bool addPrev(Node*);
  
    //=deleters
    
    //deletes this Node
    void deleteMe();
    void removeMe();
    
    private:
    //what is the next Node?
    Node* next;
    //what is the previous Node?
    Node* previous;
    //what are we storing?
    T* value;
};
