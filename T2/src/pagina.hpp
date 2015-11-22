#ifndef PAGINA_HPP
#define PAGINA_HPP
#include <vector>
#include <fstream>
#include <node.hpp>
#define TAMANHO_PAGINA (16)
#define NOME_PAGINA ("indicelista.%03d.bt")

volatile unsigned int NUMERO_PAGINA = 1;

class Pagina
{
	char* gerar_nome_pagina(unsigned int);
	void carregar_pagina();
	void escrever_pagina();
	unsigned int no_pagina;
	unsigned int no_pagina_pai;
public:
	Pagina();
	void adicionar(std::string, unsigned int);
	void salvar();
	void definir_pagina(unsigned int);
	unsigned int tamanho();
	std::vector<Node> dados;
	std::vector<unsigned int> filhos;
	friend class Node;
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

char* Pagina::gerar_nome_pagina(unsigned int numero)
{
	char *nome = (char*) malloc(sizeof(char) * 20);
	sprintf(nome, NOME_PAGINA, numero);
	return nome;
}

void Pagina::carregar_pagina()
{
	std::fstream pagina;
	char *nome_pagina = gerar_nome_pagina(no_pagina);
	std::string pk;
	unsigned int no_linha;

	pagina >> pk;
	while (pk.length() > 0)
	{
		pagina >> no_linha;
		Node no(pk, no_linha);
		dados.push_back(no);
		pagina >> pk;
	}

	free(nome_pagina);
	pagina.close();
}

void Pagina::escrever_pagina()
{
	std::fstream pagina;
	char *nome_pagina = gerar_nome_pagina(NUMERO_PAGINA);
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

Pagina::Pagina()
{
	no_pagina = 0;
	no_pagina_pai = -1;
}

void Pagina::adicionar(std::string dado, unsigned int no_linha)
{
	Node no(dado, no_linha);
	unsigned int i;

	if (filhos.size() > 0) {
		/* ainda não está em uma folha */
		for (i = 0; i < dados.size(); ++i)
			if (dados[i].get_pk().compare(no.get_pk()) > 0)
				break;
		Pagina filha;
		filha.definir_pagina(filhos[i]);
		filha.carregar_pagina();
		filha.adicionar(dado, no_linha);
		filha.salvar();
	}
	else {
		/* está em uma folha */
		for (i = 0; i < dados.size(); ++i)
			if (dados[i].get_pk().compare(no.get_pk()) > 0)
				break;
		dados.insert(dados.begin() + i, no);

		if (dados.size() >= TAMANHO_PAGINA) {
			escrever_pagina();
			dados.clear();
			++NUMERO_PAGINA;
		}
	}
}

void Pagina::salvar()
{
	escrever_pagina();
}

void Pagina::definir_pagina(unsigned int pag)
{
	no_pagina = pag;
}

unsigned int Pagina::tamanho()
{
	return dados.size();
}

#undef NOME_PAGINA
#undef TAMANHO_PAGINA
#endif /* end of include guard: PAGINA_HPP */
