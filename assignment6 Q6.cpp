// HuffTrees.cpp : Defines the entry point for the console application.
//

#include "Huffman_Tree.h"
#include <iostream>
#include <string>
using namespace std; 
int main()
{
	
	Huff_Data<string> hickory(2, "hickory");
	Huff_Data<string> dickory(2, "dickory");
	Huff_Data<string> dock(2, "dock");
	Huff_Data<string> the(4, "the");
	Huff_Data<string> mouse(2, "mouse");
	Huff_Data<string> ran(2, "ran");
	Huff_Data<string> up(1, "up");
	Huff_Data<string> clock(2, "clock");
	Huff_Data<string> struck(1, "struck");
	Huff_Data<string> one(1, "one");
	Huff_Data<string> down(1, "down");




	std::ostringstream code;
	std::vector<Huff_Data<string>> huff_Data {hickory,dickory,dock,the,mouse,ran,up,clock,struck,one,ran,down };
	Huffman_Tree<string> huff_tree;
	huff_tree.build_tree(huff_Data);
	huff_tree.print_code(code);
	std::string result = code.str();
	std::cout << result;

	result = huff_tree.decode("010");
	system("pause"); 
	
	return 0;
}

