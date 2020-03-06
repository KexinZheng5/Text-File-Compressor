#pragma once
#include <sstream>
#include <bitset>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include "binaryHeap.h"
#include "arrayQueue.h"
#include "hnode.h"

/*
will be called after some file has been read into a string
*/
HNode buildHuffmanTree(std::string s)
{
	/*
	create meldable heap and map
	*/
	BinaryHeap<HNode> mh;
	std::map<char, int> m;
	
	/*
	count the weight of each character
	*/
	for(auto e : s)
		m[e]++;
	/*
	create HNode for each character and add to the meldable heap
	*/
	for (auto e : m)
	{
		HNode n(e.first, e.second); 
		mh.add(n);
	}
	
	/*
	while there are more than 1 node in the meldable heap
	*/
	while(mh.size()>1)
	{
		/*
		pop out and store the 2 smallest weighted HNode in the meldable heap
		create an internal node that has the sum of u1's and u1's weight
		*/
		HNode u1 = mh.remove();
		HNode u2 = mh.remove();
		HNode internal(u1 + u2);
		/*
		allocate memory to store u1 and u2
		*/
		HNode* n1 = new HNode(u1);
		HNode* n2 = new HNode(u2);
		/*
		connect the 3 nodes by making n1 the left child of internal and n2 the right child of internal. 
		*/
		internal.l = n1; 
		internal.r = n2; 
		/*
		add internal to the meldable heap
		*/
		mh.add(internal); 
	}
	/*
	remove the HNode in the meldable heap, and the HNode should form a huffman tree
	*/
	return mh.remove();
}

/*
free memory allocated for the HNodes using bf-travers
*/
void freeMemory(HNode root)
{
	ArrayQueue<HNode*> nodes; 
	nodes.add(root.l);
	nodes.add(root.r);
	while(nodes.size() != 0)
	{
		HNode* u = nodes.remove();
		if (u->l != nullptr)
			nodes.add(u->l);
		if (u->r != nullptr)
			nodes.add(u->r);
		delete u; 
	}
}

/*
traverse through the Huffman tree to generate a map for encoding
*/
void traverse(HNode* u, std::string code, std::map<char, std::string> &table)
{
	if(u->l->c != 0)
		table.insert(std::pair<char, std::string>(u->l->c, code+"0"));
	else
		traverse(u->l, code+"0", table);
	if(u->r->c != 0)
		table.insert(std::pair<char, std::string>(u->r->c, code+"1"));
	else
		traverse(u->r, code+"1", table);
}

/*
encode
*/
void encode(HNode &root, std::string str)
{
	/*
	get a map to encode the string
	*/
	std::map<char, std::string> table;
	traverse(root.l, "0", table); 
	traverse(root.r, "1", table);
	
	/*
	convert to string
	*/
	std::ostringstream oss;
	for(auto c : str)
		oss << table[c];
	std::string converted = oss.str(); 
	
	/*
	store into file
	*/
	int size = converted.length();
	std::ofstream ofs("encode", std::ofstream::binary);
	ofs.write(reinterpret_cast<char *>(&size), 4);
	
	char buffer;
	int i = 0;
	
	while(size > 0)
	{
		buffer = 0;
		for(int j = 0; j < 8; j++)
		{
			buffer += converted[i%converted.length()] - '0';
			size--;
			i++;
			if (j < 7)
				buffer = buffer << 1; 
		}
		ofs.write(reinterpret_cast<char *>(&buffer), 1);
	}
	ofs.close();
}

/*
decode
*/
void decode(HNode &root)
{
	HNode* ptr = &root; 
	
	std::ofstream ofs("decode", std::ofstream::binary);
	std::ifstream ifs("encode");
	if(not ifs) std::cout << "encode not opened" << std::endl;
	if(not ofs) std::cout << "decode not opened" << std::endl;
	
	/*
	get number of bits needed to be decoded
	*/
	int size;
	ifs.read(reinterpret_cast<char *>(&size),4);

	int i; 
	char buffer;
	while(1)
	{
		ifs.read(reinterpret_cast<char *>(&buffer),1);
		i = 7; 
		std::bitset<8> bs(buffer);
		//std::cout << bs << std::endl; 
		while(i >= 0)
		{
			//std::cout << bs[i] << std::endl; 
			if(bs[i])
				ptr = ptr->r; 
			else
				ptr = ptr->l; 
			if(ptr->c != 0)
			{
				ofs.write(reinterpret_cast<char *>(&(ptr->c)), 1);
				ptr=&root; 
			}
			i--; 
			size--;
			if(size <= 0)
				goto finish;
		}
	}

finish:
	ifs.close();
	ofs.close();
}
