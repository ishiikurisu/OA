#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <btree.hpp>

class Node
{
	std::string pk;
	size_t linha;
public:
	Node();
	Node(std::string, size_t);
	std::string get_pk();
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

std::string Node::get_pk()
{
	return pk;
}

void Node::mostrar()
{
	std::cout << "- " << pk << ": " << linha << std::endl;
}

#endif
