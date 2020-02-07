/*test.cpp*/

//
// Lab week 07:
// 
// AVL unit tests based on Catch framework.  We are assuming the AVL class is now
// balancing the trees in these tests.
//

#include <iostream>
#include <vector>

#include "avl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) AVL tree with 4 nodes") 
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 4 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);
  avl.insert(125, -125);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 4);
  REQUIRE(avl.height() == 2);

  REQUIRE(keys[0] == 50);
  REQUIRE(values[0] == -50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(values[1] == -100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(values[2] == -125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(values[3] == -150);
  REQUIRE(heights[3] == 1);
}

TEST_CASE("(2) empty tree") 
{
  avltree<int, int>  avl;

  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
}

TEST_CASE("(3) just one node") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 88);

  REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 123);
	REQUIRE(values[0] == 88);
  REQUIRE(heights[0] == 0);
}
TEST_CASE("(4) Right rotate") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 88);
	avl.insert(121, 44);
	avl.insert(120, 66);
	avl.insert(119, 58);

  REQUIRE(avl.size() == 4);
  REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 119);
	REQUIRE(values[0] == 58);
  REQUIRE(heights[0] == 0);
	
		REQUIRE(keys[2] == 121);
	REQUIRE(values[2] == 44);
  REQUIRE(heights[2] == 2);
	
	REQUIRE(keys[3] == 123);
	REQUIRE(values[3] == 88);
  REQUIRE(heights[3] == 0);
}
TEST_CASE("(5) Right rotate") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 88);
	avl.insert(121, 44);
	avl.insert(120, 66);
	avl.insert(119, 58);
	avl.insert(10, 11);
	avl.insert(20, 54);

  REQUIRE(avl.size() == 6);
  REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 10);
	REQUIRE(values[0] == 11);
  REQUIRE(heights[0] == 1);
	
		REQUIRE(keys[2] == 119);
	REQUIRE(values[2] == 58);
  REQUIRE(heights[2] == 2);
	
	REQUIRE(keys[3] == 120);
	REQUIRE(values[3] == 66);
  REQUIRE(heights[3] == 0);
}
TEST_CASE("(6) left rotate") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 88);
	avl.insert(121, 44);
	avl.insert(120, 66);
	avl.insert(119, 58);
	avl.insert(10, 11);
	avl.insert(20, 54);
	avl.insert(50, 900);

  REQUIRE(avl.size() == 7);
  REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 10);
	REQUIRE(values[0] == 11);
  REQUIRE(heights[0] == 0);
	
		REQUIRE(keys[3] == 119);
	REQUIRE(values[3] == 58);
  REQUIRE(heights[3] == 2);
	
	REQUIRE(keys[6] == 123);
	REQUIRE(values[6] == 88);
  REQUIRE(heights[6] == 0);
}

TEST_CASE("(7) insert ascending") 
{
  avltree<int, int>  avl;
	for(int i = 0; i < 2000; i++){
	avl.insert(i, i);
	}

  REQUIRE(avl.size() == 2000);
  REQUIRE(avl.height() == 10);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 0);
	REQUIRE(values[0] == 0);
  REQUIRE(heights[0] == 0);
	
		REQUIRE(keys[3] == 3);
	REQUIRE(values[3] == 3);
  REQUIRE(heights[3] == 2);
	
	REQUIRE(keys[6] == 6);
	REQUIRE(values[6] == 6);
  REQUIRE(heights[6] == 0);
	
	REQUIRE(keys[1999] == 1999);
	REQUIRE(values[1999] == 1999);
  REQUIRE(heights[1999] == 0);
	
	REQUIRE(keys[456] == 456);
	REQUIRE(values[456] == 456);
  REQUIRE(heights[456] == 0);
}
TEST_CASE("(8) right left rotate") 
{
  avltree<int, int>  avl;
	
	avl.insert(500, 88);
	avl.insert(100, 44);
	avl.insert(1000, 66);
	avl.insert(5000, 58);
	avl.insert(750, 1651);
	avl.insert(800, 10);


  REQUIRE(avl.size() == 6);
  REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	

	
	REQUIRE(keys[0] == 100);
	REQUIRE(values[0] == 44);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[2] == 750);
	REQUIRE(values[2] == 1651);
	REQUIRE(heights[2] == 2);
	
	REQUIRE(keys[3] == 800);
	REQUIRE(values[3] == 10);
	REQUIRE(heights[3] == 0);
	
	REQUIRE(keys[4] == 1000);
	REQUIRE(values[4] == 66);
	REQUIRE(heights[4] == 1);

	REQUIRE(keys[5] == 5000);
	REQUIRE(values[5] == 58);
	REQUIRE(heights[5] == 0);

}
TEST_CASE("(9) left right  rotate") 
{
  avltree<int, int>  avl;
	avl.insert(1000, 88);
	avl.insert(500, 44);
	avl.insert(1250, 66);
	avl.insert(750, 58);
	avl.insert(850, 1651);
	avl.insert(800, 10);


  REQUIRE(avl.size() == 6);
  REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 500);
	REQUIRE(values[0] == 44);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 750);
	REQUIRE(values[1] == 58);
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 800);
	REQUIRE(values[2] == 10);
	REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 850);
	REQUIRE(values[3] == 1651);
	REQUIRE(heights[3] == 2);
	
	REQUIRE(keys[4] == 1000);
	REQUIRE(values[4] == 88);
	REQUIRE(heights[4] == 1);

	REQUIRE(keys[5] == 1250);
	REQUIRE(values[5] == 66);
	REQUIRE(heights[5] == 0);
	

}

TEST_CASE("(10) Distance test") 
{
  avltree<int, int>  avl;
	avl.insert(1000, 88);
	avl.insert(500, 44);
	avl.insert(1250, 66);
	avl.insert(750, 58);
	avl.insert(850, 1651);
	avl.insert(800, 10);

	avl.insert(45, 88);
	avl.insert(789, 44);
	avl.insert(56, 66);
	avl.insert(489, 58);
	avl.insert(738, 1651);
	avl.insert(416, 10);

  REQUIRE(avl.size() == 12);
  REQUIRE(avl.height() == 3);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	int dist1 = avl.distance(800, 1000);
	REQUIRE(dist1 == 2);
	int dist2 = avl.distance(800, 738);
	int dist3 = avl.distance(1250, 45);
	int dist4 = avl.distance(750, 750);
	int dist5 = avl.distance(10, 850);
	int dist6 = avl.distance(750, 60);
	int dist7 = avl.distance(95, 876);
	int dist8 = avl.distance(56, 416);
	int dist9 = avl.distance(750, 738);
	int dist10 = avl.distance(750, 1250);
	int dist11 = avl.distance(750, 1000);
	int dist12 = avl.distance(738, 789);
	int dist13 = avl.distance(45, 489);
	int dist14 = avl.distance(45, 56);
	int dist15 = avl.distance(500, 500);
	
	REQUIRE(dist2 == 5);
	REQUIRE(dist3 == 6);
	REQUIRE(dist4 == 0);
	REQUIRE(dist5 == -1);
	REQUIRE(dist6 == -1);
	REQUIRE(dist7 == -1);
	REQUIRE(dist8 == 1);
	REQUIRE(dist9 == 3);
	REQUIRE(dist10 == 3);
	REQUIRE(dist11 == 2);
	REQUIRE(dist12 == 6);
	REQUIRE(dist13 == 2);
	REQUIRE(dist14 == 1);
	REQUIRE(dist15 == 0);
	
	REQUIRE(keys[0] == 45);
	REQUIRE(values[0] == 88);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 56);
	REQUIRE(values[1] == 66);
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 416);
	REQUIRE(values[2] == 10);
	REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 489);
	REQUIRE(values[3] == 58);
	REQUIRE(heights[3] == 2);
	
	REQUIRE(keys[4] == 500);
	REQUIRE(values[4] == 44);
	REQUIRE(heights[4] == 1);

	REQUIRE(keys[5] == 738);
	REQUIRE(values[5] == 1651);
	REQUIRE(heights[5] == 0);
	

}

TEST_CASE("(11) small Distance test") 
{
  avltree<int, int>  avl;

	avl.insert(0, 0);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	cout << "HERE" << endl;
	int dist1 = avl.distance(0, 0);
	cout << "WQERQ" << endl;
	int dist2 = avl.distance(13, 0);
	
	
	REQUIRE(dist1 == 0);
	REQUIRE(dist2 == -1);
	

}
TEST_CASE("(12) two node Distance test") 
{
  avltree<int, int>  avl;

   avl.insert(50, 1);
   avl.insert(25, 1);
   avl.insert(75, 1);
   avl.insert(15, 1);
   avl.insert(35, 1);
   avl.insert(65, 1);
   avl.insert(85, 1);
   avl.insert(10, 1);
   avl.insert(20, 1);
   avl.insert(30, 1);
   avl.insert(40, 1);
   avl.insert(60, 1);
   avl.insert(70, 1);
   avl.insert(80, 1);
   avl.insert(90, 1);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	//cout << "HERE" << endl;
	int dist1 = avl.distance(50, 50);

	int dist2 = avl.distance(50, 75);
	int dist3 = avl.distance(4, 0);
	int dist4 = avl.distance(-5, 50);
	int dist5 = avl.distance(90, 65);
	int dist6 = avl.distance(60, 20);
	int dist7 = avl.distance(25, 40);
	int dist8 = avl.distance(25, 30);
	int dist9 = avl.distance(15, 85);
	int dist10 = avl.distance(85, 15);
	
	REQUIRE(dist1 == 0);
	REQUIRE(dist2 == 1);
	REQUIRE(dist3 == -1);
	REQUIRE(dist4 == -1);
	REQUIRE(dist5 == 3);
	REQUIRE(dist6 == 6);
	REQUIRE(dist7 == 2);
	REQUIRE(dist8 == 2);
	REQUIRE(dist9 == 4);
	REQUIRE(dist10 == 4);

}