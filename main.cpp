#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "avl.h"

using namespace std;

int main(){
	
	avltree<int, int> avl;
	


	avl.insert(123, 88);
	avl.inorder();
	avl.insert(121, 44);
	avl.inorder();
	avl.insert(120, 66);
	avl.inorder();
	avl.insert(119, 58);
	avl.inorder();
	avl.insert(10, 11);
	avl.inorder();
	avl.insert(20, 54);
	avl.inorder();
	avl.insert(50, 900);
	
	avl.inorder();
	int dist = avl.distance(10, -50);
	cout << "Distance: " << dist << endl;
	/*
	for(int i = 200; i < 1000; i++){
		avl.insert(i, i);
	}
	//avl.inorder();
	int* x = avl.search(500);
	cout << *x << endl;
	
	vector<int> v = avl.inorder_heights();
	for(int i = 0; i < v.size();i++){
		cout << v[i] << endl;
	}*/
	cout << avl.height() << endl;
	
}