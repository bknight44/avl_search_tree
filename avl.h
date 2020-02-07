#pragma once

#include <iostream>
#include <algorithm>  // std::max
#include <cstdlib>    // std::abs
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

template<typename TKey, typename TValue>
class avltree
{
private:
  struct NODE
  {
    TKey   Key;
    TValue Value;
    int    Height;
    NODE*  Left;
    NODE*  Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)


  void _inorder(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder(cur->Left);
      cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
      _inorder(cur->Right);
    }
  }
  void _inorder_heights(NODE* cur, std::vector<int>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_heights(cur->Left, V);
      V.push_back(cur->Height);
      _inorder_heights(cur->Right, V);
    }
  }
  void _inorder_keys(NODE* cur, std::vector<TKey>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_keys(cur->Left, V);
      V.push_back(cur->Key);
      _inorder_keys(cur->Right, V);
    }
  }

  void _inorder_values(NODE* cur, std::vector<TValue>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_values(cur->Left, V);
      V.push_back(cur->Value);
      _inorder_values(cur->Right, V);
    }
  }
  void _copytree(NODE* cur)
  {
    if (cur == nullptr){
      return;
    }else
    {
      //
      // to copy and build an exact copy, we need to "visit" cur
      // first and insert that (key, value) pair first.  That way
      // all the nodes to the left will properly go to the left,
      // all the node to the right will properly go to the right.
      //
      insert(cur->Key, cur->Value);

      _copytree(cur->Left);
      _copytree(cur->Right);
	  }
    }
	
	void _fixHeights(NODE* N){
   //first find the node while stacking all prior nodes
      //cout << N->Key;
      NODE* search = Root;
      stack<NODE*> nodes;
      
      while(search != nullptr){
         nodes.push(search);
         if(N->Key == search->Key){
            break;  
         }else if(N->Key > search->Key){ //go right
            search = search->Right;
         }else{// go left
            search = search->Left;
         }
      }
      //now pop and update heights
      
      while(!nodes.empty()){
            int left,right;
            if(nodes.top()->Left == nullptr){
               left = -1;
            }else{
               left = nodes.top()->Left->Height;
            }if(nodes.top()->Right == nullptr){
               right = -1;
            }else{
              right = nodes.top()->Right->Height;
            }
           nodes.top()->Height = max(left, right) + 1;
           nodes.pop();
      }
	}

void _RightRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);

    //
    // TODO
    //
    NODE* temp;
    if(Parent == nullptr){
		 Root = N->Left; 
		 temp = N->Left;
		 //Parent = N->Left;
    }else if(Parent->Key > N->Key){//were on the left
         Parent->Left = N->Left;
         temp =  N->Left;
    }
    else{//were on the right
      Parent->Right = N->Left;
      temp =  N->Left;
      //Parent = N->Left;
      
    }
    N->Left = temp->Right;
    temp->Right = N;
    
    _fixHeights(N);
   // Parent->Height = max(Parent->Left->Height, Parent->Right->Height) + 1;
    
    
  }

  void _LeftRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and R must exist
    assert(N->Right != nullptr);
    
    //
    // TODO
    //
   NODE* temp;
    if(Parent == nullptr){
     Root = N->Right; 
     temp =  N->Right;
     //Parent = N->Left;
    }else if(Parent->Key > N->Key){//were on the left
         Parent->Left = N->Right;
         temp =  N->Right;
    }
    else{//were on the right
      Parent->Right = N->Right;
      temp =  N->Right;
      //Parent = N->Left;
      
    }
    N->Right = temp->Left;
    temp->Left = N;
    
    _fixHeights(N);
  }

void _walkUpTreeAndRotate(stack<NODE*>* node, NODE* newNode){ //I pass the stack by reference.
	NODE* cur;
	stack<NODE*> nodes = *node;
	NODE* previousNode = newNode; //this keeps track of the direction that we pointed to last while coming up the tree
	NODE* prevPreviousNode = nullptr; //this keeps track of the direction of the node Before previousNode
    stack<NODE*> checkNodes;
	//int rotateCase = 0; // zero is for no rotation
    while (!nodes.empty() && nodes.top() != nullptr)
    {
		
		cur = nodes.top();
	  //cout << "THE KEY: " << cur->Key << endl;
		checkNodes.push(cur);
      nodes.pop();
	  if(nodes.empty()){
		  //cout << "EMPTY" << endl;
		  NODE* temp = nullptr;
		  nodes.push(temp);
	  }
      int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
	  
	  int rotation = _ballanced(hL, hR);//check if rotations are needed
	  //cout << "Rotation Value: " << rotation << endl;
	  if(rotation != 0){
		  //cout << "prevPreviousNode: " << prevPreviousNode << endl;
	  	  if(prevPreviousNode != nullptr){// this is the first time we could possibly have a need for rotate
		  //get first right or left
		  NODE* tempNODE; 
		  if(checkNodes.top()->Left == previousNode){//first is left
			  tempNODE = checkNodes.top()->Left;
			  checkNodes.pop();
			  if(checkNodes.top()->Left == prevPreviousNode){//second is left... so case 1
				  //rotateCase = 1;
				  _RightRotate(nodes.top(), cur);
			  }else{// second case is right... case 2
				  //rotateCase = 2;
				  _LeftRotate(cur, tempNODE);
				  _RightRotate(nodes.top(), cur);
			  }
		  }else{//first was right
			  tempNODE = checkNodes.top()->Right;
			  checkNodes.pop();
			  //cout << "checkNodes: " << checkNodes.top()->Left << endl;
			  //cout << "prevPreviousNode: " << prevPreviousNode << endl;
			  if(checkNodes.top()->Left == prevPreviousNode){//second is left... so case 3
				  //rotateCase = 3;
				  _RightRotate(cur, tempNODE);
				  _LeftRotate(nodes.top(), cur);
			  }else{// also right... case 4
				  //rotateCase = 4;
				  _LeftRotate(nodes.top(), cur);
			  }
		  }
		  //cout <<"Rotation: " << rotateCase << endl;
		  checkNodes.push(tempNODE);//get this back on the stack for later
	  }
	  }

	   hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
       hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
      int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur){  // didn't change, so no need to go further:
        break;
		}
      else { // height changed, update and keep going:
        cur->Height = hCur;
		
		}
		
		//reset the previous nodes now that we are moving to the next
		//there will never be a blip in this 
		prevPreviousNode = previousNode;
		previousNode = cur;
		
		
		//rotateCase = 0; //resetting rotate case to default
    }
}


  int _ballanced(int leftHeight, int rightHeight){ //I want to make this a private function ***reminder***
	  int diff = std::abs(leftHeight - rightHeight);
	  
	  if(diff <= 1){ //balanced return 0
		  return 0;
	  }else if(rightHeight > leftHeight){//right side is larger 
		  return 1;
	  }else{//left side must be larger
		  return -1;
	  }
  
  }
  
  void _clear(NODE* cur){
	  if (cur == nullptr)
		  return;
		else
		{
		  _clear(cur->Left);
		  _clear(cur->Right);
		  delete cur;
		  Size--;// only for testing to make sure this gets every node
		}
  }
	int _travelTree(NODE* cur, TKey val){//Takes in the top node of a sub tree and searches
		int steps = 1; //we will start at 1. Because we will hand this funtion the root of
		//A sub tree that we have already taken a step into
		while(cur != nullptr){
			if(cur->Key == val){
				return steps;
			}else if(cur->Key > val){
				cur = cur->Left;
			}else{
				cur = cur->Right;
			}
			steps++;
		}
		//if we made it here cur must be null
		return -1;
		
	}
  
public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avltree()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor:
  //
  avltree(avltree& other)
  {
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
  }
  
	//destructor
	virtual ~avltree(){
		clear();
		
	}
	
	
	void clear(){//wipeout all nodes properly
	
	_clear(Root);
	Root = nullptr;
	//Size = 0; //will test with size--
	
	}
	
	
	
  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Returns the height of tree; the height of an empty tree is
  // defined as -1.
  //
  int height()
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning a pointer to the 
  // value if found and nullptr if not.  We return a pointer so the caller
  // may update the underlying value if needed.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return &cur->Value;
      }

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  

    // if get here, not found
    return nullptr;
  }


  void insert(TKey key, TValue value){
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      nodes.push(cur);  // stack so we can return later:

      if (key < cur->Key){  // search left:
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 
    NODE* newNode;
    newNode = new NODE();
    newNode->Key = key;
    newNode->Value = value;
    newNode->Height = 0;  // leaf node -> sub-tree of height 0:
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr){
      Root = newNode;
    }else if (key < prev->Key){
      prev->Left = newNode;
    }else{
      prev->Right = newNode;
	}
    // 
    // 4. update size:
    //
    Size++;
	//nodes.push(newNode);
	/*
	while (!nodes.empty())
    {
		cout << nodes.top()->Key << endl;
		nodes.pop();
	}*/
    //
    // 5. walk back up tree using stack and update heights.
    //
    _walkUpTreeAndRotate(&nodes, newNode);
    
	
    return;
  }
  


	int distance(TKey k1, TKey k2){
		//first I get the lower key
		//AND dont forget the case where key is not found in the tree. return -1 then
		TKey low;
		TKey high;
		if(k1 < k2){
			low = k1;
			high = k2;
		}else if(k2 < k1){
			low = k2;
			high = k1;
		}else{
			low = k1;
			high = k2; //now just check if one of these exist since they are equal
		}
		//create a stack to our first key
		stack<NODE*> nodes;
		NODE* search = Root;
		//nodes.push(search);
		while(search != nullptr){
			if(search->Key == low){
				break;
			}else if(search->Key > low){// go to the left
				nodes.push(search);
				 search = search->Left;
			}else{//search is too small.  go right
				nodes.push(search);
				search = search->Right;
			}
			//nodes.push(search);
		}
		if(search == nullptr){ //the low key does not exist
			return -1;
		}
		if(low == high){//now that we know low exists we can check this
			return 0;
		}
		//now if the program is here we have found our low key
		//now we need to check to the right first
		//then if it is not there, we go up and then to the right
		//
		//lets check to the right
		int stepsToRight = _travelTree(search->Right, high);//search is the low key
		if(stepsToRight != -1){//Hey we found the value to the right
			return stepsToRight; //DONE!
		}
		//if we are here then we did not find it on the right
		//and now we need to head up our stack
		//cout << "low: " << low << endl;
		//cout << "High: " << high << endl;
		if(nodes.empty()){//it is not in the tree and the tree is only size one
			return -1;
		}
		NODE* subRoot = nodes.top();
		int subRootHeight = 0;
		int steps = 0;
		while(!nodes.empty()){
			steps++;//increment first because we are taking a step right away and searching
			if(nodes.top()->Key < high){// keep going up
				if(subRoot->Key <= nodes.top()->Key){//only take the new node if it is greater then our last node
					subRoot = nodes.top();
					subRootHeight = steps;
				}
				nodes.pop();
			}else if(nodes.top()->Key == high){//the node we wanted was in the stack!
				return steps;
			}else if(nodes.top()->Key > high){//oops we went to far... leave the loop and decrement our step
				steps--;
				break;
			}
		}
		steps = subRootHeight;
		//cout << "Subroot: " << subRoot->Key << endl;
		//
		//now all that is left to do is look down through the tree
		//
		
		stepsToRight = _travelTree(subRoot->Right, high);
		//cout << "Steps: " << steps << endl;
		//cout << "steps to the right: " << stepsToRight << endl;
		if(stepsToRight == -1){//the high key did not exist!
			return -1;
		}else{
			return (steps + stepsToRight);
		}
	}



  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
    cout << "Inorder: ";

    _inorder(Root);

    cout << endl;
  }

  std::vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  }

  std::vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  }

  std::vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  }
  
  };