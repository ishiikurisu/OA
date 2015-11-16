#ifndef BTREE_H
#define BTREE_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <node.hpp>
#define TAMANHO_PAGINA 16
#define NOME_PAGINA ("indicelista.%03d.bt")

class BTree
{
	char* gerar_nome_pagina(unsigned int);
	void carregar_pagina();
	void escrever_pagina();
	std::vector<Node> dados;
	std::vector<std::string> enderecos;
	int numero_paginas;
public:
	BTree();
	void adicionar(std::string, unsigned int);
	void mostrar();
	friend class Node;
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

char* BTree::gerar_nome_pagina(unsigned int numero)
{
	char *nome = (char*) malloc(sizeof(char) * 256);
	sprintf(nome, NOME_PAGINA, numero_paginas);
	return nome;
}

void BTree::carregar_pagina()
{

}

void BTree::escrever_pagina()
{
	std::fstream pagina;
	char *nome_pagina = gerar_nome_pagina(numero_paginas);
	std::vector<Node>::iterator no;

	pagina.open(nome_pagina, std::fstream::out);

	for (no = dados.begin(); no != dados.end(); ++no)
	{
		pagina << no->pk << " " << no->linha << std::endl;
	}

	free(nome_pagina);
	pagina.close();
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

BTree::BTree()
{
	numero_paginas = 1;
}

void BTree::adicionar(std::string dado, unsigned int no_linha)
{
	Node no(dado, no_linha);
	unsigned int i = 0;

	/* adicionar ordenado */
	for (i = 0; i < dados.size(); ++i)
		if (dados[i].get_pk().compare(no.get_pk()) > 0)
			break /* ou vá a outra página, se tiver */;
	dados.insert(dados.begin() + i, no);

	/* checar se deve dividir a página */
	if (dados.size() >= TAMANHO_PAGINA) {
		// enquanto não dividimos a página...
		escrever_pagina();
		dados.clear();
		++numero_paginas;
	}
}

void BTree::mostrar()
{
	std::vector<Node>::iterator it;

	escrever_pagina();
	std::cout << "--- # BTree" << std::endl;
	for (it = dados.begin(); it != dados.end(); ++it)
		it->mostrar();

	std::cout << "..." << std::endl;
}

#endif /* end of include guard: BTREE_H */
