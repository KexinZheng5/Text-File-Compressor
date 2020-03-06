#pragma once

struct HNode
{
	/*
	c: the character
	weight: the frequency of char in text
	l: left child
	r: right child
	*/
	char c;
	int weight;
	HNode* l; 
	HNode* r; 
	/*
	constructors
	*/
	HNode() : c(0), weight(0){ l = r = nullptr; }
	HNode(int w): c(0), weight(w){ l = r = nullptr; }
	HNode(char ch, int w): c(ch), weight(w){ l  = r = nullptr; }
	
	/*
	operator overloading
	*/
	bool operator<(HNode hn){ return weight < hn.weight; }
	bool operator>(HNode hn){ return weight > hn.weight; }
	bool operator==(HNode hn){ return weight == hn.weight; }
	bool operator==(int n){ return weight == n; }
	int operator+(HNode hn){ return weight + hn.weight; }
	int operator*(int n){ return weight * n; }
	bool operator!=(int n){ return weight != n; }
};
