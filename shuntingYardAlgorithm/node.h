/* 
  Daren Kostov

  simple node class
  
*/

#ifndef NODE
#define NODE


template<class T>
class Node{

  public:

    //empty constructor
    Node();

    //deconstrictor
    ~Node();

    //initialize a node with a value
    Node(T);
  
    //sets the next node
    void setNext(Node*);
  
    //sets the previous node
    void setPrevious(Node*);
  
    //gives you a pointer to the next node
    Node* getNext();
  
    //gives you a pointer to the next node
    Node* getPrevious();
  
    //gives you the value stored
    T getValue();

    //sets the internal value
    void setValue(T);
  
  protected:
    
    Node* next;
    Node* previous;

    
    T value;

};


#endif