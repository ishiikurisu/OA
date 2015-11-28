#ifndef PAGINA_HPP
#define PAGINA_HPP
#include <fstream>
#include <iostream>
#include <vector>
#include <node.hpp>
#define TAMANHO_PAGINA (16)
#define NOME_PAGINA ("indicelista.%03d.bt")

volatile unsigned int NUMERO_PAGINA = 1;

class Pagina
{
    char* gerar_nome_pagina(unsigned int);
    void carregar_pagina();
    unsigned int no_pagina;
    unsigned int no_pai;
    std::vector<Node> dados;
    std::vector<unsigned int> filhas;
public:
    Pagina() { no_pai = -1; };
    Pagina(unsigned int);
    ~Pagina() {};
    Pagina achar_filha(Node);
    void adicionar(Node);
    bool overflow();
    // void dividir_filhas();
    // void lidar_com_pai(Node);
    void definir_pagina(unsigned int);
    void definir_pai(unsigned int);
    void salvar();
    std::string escrever();
    std::string identificar();
    friend class Node;
    friend class BTree;
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

char* Pagina::gerar_nome_pagina(unsigned int no)
{
    char *nome = new char[20];
    sprintf(nome, NOME_PAGINA, no);
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

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

Pagina::Pagina(unsigned int no) : Pagina::Pagina()
{
    no_pagina = no;
    carregar_pagina();
}

Pagina Pagina::achar_filha(Node no)
{
    unsigned int i;

    if (filhas.size() == 0)
        return (*this);
    for (i = 0; i < dados.size(); ++i)
        if (dados[i].get_pk().compare(no.get_pk()) > 0)
            break;
    Pagina filha(filhas[i]);
    filha.definir_pai(no_pagina);
    return filha.achar_filha(no);
}

void Pagina::adicionar(Node no)
{
    unsigned int i;
    for (i = 0; i < dados.size(); ++i)
        if (dados[i].get_pk().compare(no.get_pk()) > 0)
            break;
    dados.insert(dados.begin() + i, no);
    salvar();
}

bool Pagina::overflow()
{
    return (filhas.size() > 0);
}

void Pagina::definir_pagina(unsigned int no)
{ no_pagina = no; }
void Pagina::definir_pai(unsigned int no)
{ no_pai = no; }

void Pagina::salvar()
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

std::string Pagina::identificar()
{
    std::string id;
    id += no_pagina;
    return id;
}

std::string Pagina::escrever()
{
    std::string data;
    std::vector<Node>::iterator it;

    data += "--- # " + identificar() + "\n";
    for (it = dados.begin(); it != dados.end(); ++it)
    {
        data += "- " + (*it).get_pk() + "\n";
    }
    data += "...\n";

    return data;
}

#endif /* end of include guard: PAGINA_HPP */
