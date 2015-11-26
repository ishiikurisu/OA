#ifndef PAGINA_HPP
#define PAGINA_HPP
#include <vector>
#include <fstream>
#include <node.hpp>
#include <toolbox.hpp>
#define TAMANHO_PAGINA (16)
#define NOME_PAGINA ("indicelista.%03d.bt")

volatile unsigned int NUMERO_PAGINA = 1;

class Pagina
{
	char* gerar_nome_pagina(unsigned int);
	void carregar_pagina();
	void escrever_pagina();
	Node adicionar_filha(Node, unsigned int);
	Node dividir_filhos();
	unsigned int no_pagina;
	unsigned int no_pagina_pai;
public:
	Pagina();
	Node adicionar(Node);
	Node adicionar(std::string, unsigned int);
	void salvar();
	void definir_pagina(unsigned int);
	void definir_pai(unsigned int);
	Pagina* dividir();
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
	char *nome_pagina = gerar_nome_pagina(no_pagina);
	std::vector<Node>::iterator no;

	pagina.open(nome_pagina, std::fstream::out);

	for (no = dados.begin(); no != dados.end(); ++no)
	{
		pagina << no->pk << " " << no->linha << std::endl;
	}

	free(nome_pagina);
	pagina.close();
}

Node Pagina::adicionar_filha(Node dado, unsigned int pagina)
{
	Pagina filha;
	filha.definir_pagina(pagina);
	filha.carregar_pagina();
	dado = filha.adicionar(dado);
	filha.salvar();
	return dado;
}

Node Pagina::dividir_filhos()
{
	Pagina *paginas = dividir();
	Pagina menor = paginas[0];
	Pagina meio  = paginas[1];
	Pagina maior = paginas[2];

	menor.definir_pagina(NUMERO_PAGINA);
	menor.definir_pai(no_pagina);
	filhos.push_back(NUMERO_PAGINA++);
	menor.escrever_pagina();

	maior.definir_pagina(NUMERO_PAGINA);
	maior.definir_pai(no_pagina);
	filhos.push_back(NUMERO_PAGINA++);
	maior.escrever_pagina();

	free(paginas);
	return meio.dados[0];
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

Pagina::Pagina()
{
	no_pagina = 0;
	no_pagina_pai = -1;
}

Node Pagina::adicionar(Node no)
{
	unsigned int i = 0;

	if (filhos.size() > 0) {
		/* ainda não está em uma folha */
		for (i = 0; i < dados.size(); ++i)
			if (dados[i].get_pk().compare(no.get_pk()) > 0)
				break;
		no = adicionar_filha(no, filhos[i]);
	}
	else {
		/* está em uma folha */
		for (i = 0; i < dados.size(); ++i)
			if (dados[i].get_pk().compare(no.get_pk()) > 0)
				break;
		dados.insert(dados.begin() + i, no);

		if (dados.size() >= TAMANHO_PAGINA) {
			toolbox::debug("dividindo");
			no = dividir_filhos();
			dados.clear();
			dados.push_back(no);
			escrever_pagina();
		}
	}

	return no;
}

Node Pagina::adicionar(std::string dado, unsigned int no_linha)
{
	Node no(dado, no_linha);
	return adicionar(no);
}

Pagina* Pagina::dividir()
{
	Pagina *outlet = new Pagina[5];
	Pagina menor;
	Pagina maior;
	Pagina meio;
	unsigned int i;

	for (i = 0; i < filhos.size()/2; ++i)
		menor.dados.push_back(dados[i]);
	meio.dados.push_back(dados[i]);
	for (++i; i < filhos.size(); ++i)
		maior.dados.push_back(dados[i]);

	outlet[0] = menor;
	outlet[1] = meio;
	outlet[2] = maior;
	return outlet;
}

void Pagina::salvar()
{
	escrever_pagina();
}

void Pagina::definir_pagina(unsigned int pag)
{
	no_pagina = pag;
}

void Pagina::definir_pai(unsigned int pai)
{
	no_pagina_pai = pai;
}

unsigned int Pagina::tamanho()
{
	return dados.size();
}

#undef NOME_PAGINA
#undef TAMANHO_PAGINA
#endif /* end of include guard: PAGINA_HPP */
