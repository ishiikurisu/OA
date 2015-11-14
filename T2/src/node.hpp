#pragma once
#include <iostream>
#include <btree.hpp>

class Node
{
	std::string pk;
	size_t linha;
public:
	Node();
	Node(std::string, size_t);
	void mostrar();
	friend class BTree;
};

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

Node::Node()
{

}

Node::Node(std::string c, size_t l)
{
	pk = c;
	linha = l;
}

void Node::mostrar()
{
	std::cout << "- " << pk << ": " << linha << std::endl;
}
