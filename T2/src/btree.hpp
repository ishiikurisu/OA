#ifndef BTREE_H
#define BTREE_H
#include <vector>
#include <string>

class BTree
{
	std::vector<std::string> dados;
public:
	BTree()	{};
	void adicionar(std::string);
};

void BTree::adicionar(std::string dado)
{
	dados.push_back(dado);
}

#endif /* end of include guard: BTREE_H */
