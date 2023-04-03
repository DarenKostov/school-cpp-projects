/*
  Daren Kostov

  a node class with right and left nodes

*/

#ifndef BINNODE
#define BINNODE

template<class T>
class BinNode{

  public:

    //empty constructor
    BinNode();

    //deconstrictor
    ~BinNode();
   
    //initialize with a value
    BinNode(T);
  
    //sets the right node
    void setRight(BinNode*);
  
    //sets the left node
    void setLeft(BinNode*);

    //gives you a pointer to the right node
    BinNode*& getRight();
  
    //gives you a pointer to the left node
    BinNode*& getLeft();

    //gives you the value stored
    T getValue();

    //sets the internal value
    void setValue(T);
  
  private:

    
    BinNode* right;
    BinNode* left;
  
    T value;

};

#endif