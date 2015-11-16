#ifndef BTREE_H
#define BTREE_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <pagina.hpp>

class BTree
{
	std::vector<std::string> enderecos;
	Pagina raiz;
	unsigned int numero_paginas;
public:
	BTree();
	void adicionar(std::string, unsigned int);
	// void mostrar();
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

BTree::BTree()
{
	raiz.definir_pagina(1);
}

void BTree::adicionar(std::string dado, unsigned int no_linha)
{
	raiz.adicionar(dado, no_linha);
}

/*
void BTree::mostrar()
{
	std::vector<Node>::iterator it;

	escrever_pagina();
	std::cout << "--- # BTree" << std::endl;
	for (it = dados.begin(); it != dados.end(); ++it)
		it->mostrar();

	std::cout << "..." << std::endl;
}
*/

#endif /* end of include guard: BTREE_H */
