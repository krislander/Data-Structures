// BinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "BinaryTree.h"

int main()
{
	BTree<int> tree;

	int nodes[] = { 65,4,10,8,13,2,78,99,45 };
	for (size_t i = 0; i < 9; i++)
	{
		tree.addLeaf(nodes[i]);
	}

	//tree.print();
	std::cout << "Smallest is: " << tree.findSmallest() << std::endl;
	std::cout << "Root is: " << tree.returnRootData() << std::endl;
	std::cout << "Count is: " << tree.count(tree.returnNode(tree.returnRootData())) << std::endl;
	std::cout << "Height is: " << tree.height(tree.returnNode(tree.returnRootData())) << std::endl;
	std::cout  << std::endl;
	tree.printChildren(44);
}
