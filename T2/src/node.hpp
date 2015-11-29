#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <btree.hpp>

class Node
{
	std::string pk;
	unsigned int linha;
public:
	Node();
	Node(std::string, unsigned int);
	std::string get_pk();
	unsigned int get_linha();
	void mostrar();
	friend class Pagina;
};

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

Node::Node()
{

}

Node::Node(std::string c, unsigned int l)
{
	pk = c;
	linha = l;
}

std::string Node::get_pk()
{
	return pk;
}

unsigned int Node::get_linha()
{
	return linha;
}

void Node::mostrar()
{
	std::cout << "- " << pk << ": " << linha << std::endl;
}

#endif
