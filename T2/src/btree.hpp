#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <vector>
#include <string>

class BTree
{
	std::vector<std::string> dados;
public:
	BTree()	{};
	void adicionar(std::string, size_t);
	void mostrar();
};

void BTree::adicionar(std::string dado, size_t no_linha)
{
	dados.push_back(dado);
}

void BTree::mostrar()
{
	std::vector<std::string>::iterator it;

	std::cout << "--- # BTree" << std::endl;
	for (it = dados.begin(); it != dados.end(); ++it)
	{
		std::cout << "- " << *it << std::endl;
	}

	std::cout << "---" << std::endl;
}

#endif /* end of include guard: BTREE_H */
