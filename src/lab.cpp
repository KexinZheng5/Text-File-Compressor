#include "buildHuffmanTree.h"

HNode buildHuffmanTree(std::string s);
void freeMemory(HNode root);
void traverse(HNode* u, std::string code, std::map<char, std::string> &table);
void encode(HNode &root, std::string str); 
void decode(HNode &root); 

const int N = 8;
int main()
{	
	/*
	read file into a string
	*/
	std::ifstream ifs("msg");
	std::ostringstream oss;
	char buffer; 
	if(not ifs) std::cout << "msg not opened" << std::endl;
	
	while(ifs)
	{
		ifs.read(reinterpret_cast<char *>(&buffer),1);
		oss << buffer; 
	}
	ifs.close();
	
	HNode ht = buildHuffmanTree(oss.str());

	encode(ht, oss.str());
	decode(ht);
	
	freeMemory(ht);

	return 0;
}



