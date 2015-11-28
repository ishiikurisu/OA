#ifndef BTREE_H
#define BTREE_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <toolbox.hpp>
#include <node.hpp>
#include <pagina.hpp>

class BTree
{
	std::vector<std::string> enderecos;
	Pagina raiz;
	unsigned int numero_paginas;
public:
	BTree();
	void adicionar(std::string, unsigned int);
	void adicionar(Node);
	// void mostrar();
	friend class Pagina;
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

void BTree::adicionar(Node no)
{
	Pagina *filha = raiz.achar_filha(no);
	filha->adicionar(no);
	// toolbox::debug(filha->escrever().c_str());

	while (filha->overflow())
	{
		std::cout << "overflow!" << std::endl;
		no = filha->dividir_filhas();
		toolbox::debug(no.get_pk().c_str());
		exit(-1);
		// filha.lidar_com_pai(no);
        /*insert to parent*/
        /*parent is now child*/
	}
}

void BTree::adicionar(std::string dado, unsigned int no_linha)
{
	Node no(dado, no_linha);
	adicionar(no);
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
