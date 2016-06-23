#include "bst.h"
#include "rbbst.h"
#include "iostream"

int main(){
	RedBlackTree<int, int> bst;
	//Node <int, int>* node = new RedBlackNode<int, int> (4, 4 , NULL);
	bst.insert(std::pair<const int, int> (3,4));

	//Node <int, int>* n2 = new RedBlackNode<int, int> (6, 6, NULL);
	bst.insert(std::pair<const int, int> (4,6));


	//Node <int, int>* n3 = new RedBlackNode<int, int> (3, 3 , NULL);
	bst.insert(	std::pair<const int, int> (5,3));
 bst.insert(	std::pair<const int, int> (6,3));
		bst.insert(	std::pair<const int, int> (8,3));
			bst.insert(	std::pair<const int, int> (7,3));
	bst.printRoot();


	BinarySearchTree<int,int>::iterator it = bst.begin();
	for ( it; it != bst.end(); ++it){
		std::cout<< (*it).first << std::endl;
	}

}