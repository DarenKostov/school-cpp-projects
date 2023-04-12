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
   
    //initialize with a value, color, and relation
    BinNode(T, char, char);

  
    //sets the right node
    void setRight(BinNode*);
  
    //sets the left node
    void setLeft(BinNode*);

    //sets the parent node
    void setParent(BinNode*);

    //sets the internal value
    void setValue(T);

    //sets the right/left variable
    void setRelation(char);
  
    //sets the color
    void setColor(char);


    //gives you a pointer to the right node
    BinNode* getRight();
  
    //gives you a pointer to the left node
    BinNode* getLeft();

    //gives you a pointer to the parent
    BinNode* getParent();

    //gives you the value stored
    T getValue();

    //gives the right/left variable
    char getRelation();
  
    //gives the color
    char getColor();

  
  
    //these could be useful
    
    //gives you The pointer to the right node
    BinNode*& Right();
  
    //gives you The pointer to the left node
    BinNode*& Left();

    //gives you The pointer to the parent
    BinNode*& Parent();

    //gives you The value stored
    T& Value();

    //gives The right/left variable
    char& Relation();
  
    //gives The color
    char& Color();


  private:

    //is it a right or left child? not the best name for a varible
    char relationship;
  
    //is it red or black
    char color;

    //the right and left children
    BinNode* right;
    BinNode* left;

    //our parent
    BinNode* parent;
  
    //what do we store?
    T value;

};

#endif
