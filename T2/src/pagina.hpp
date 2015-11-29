#ifndef PAGINA_HPP
#define PAGINA_HPP
#include <fstream>
#include <iostream>
#include <vector>
#include <node.hpp>
#define TAMANHO_PAGINA (16)
#define NOME_PAGINA ("indicelista.%03d.bt")

unsigned int NUMERO_PAGINA = 1;

class Pagina
{
    char* gerar_nome_pagina(unsigned int);
    void carregar_pagina();
    Pagina* dividir_pagina();
    unsigned int no_pagina;
    unsigned int no_mae;
    std::vector<Node> dados;
    std::vector<unsigned int> filhas;
public:
    Pagina() { no_mae = -1; };
    Pagina(unsigned int);
    ~Pagina() { };
    Pagina* achar_filha(Node);
    void adicionar(Node);
    bool overflow();
    Node dividir_filhas();
    Pagina* lidar_com_mae();
    void definir_pagina(unsigned int);
    void definir_mae(unsigned int);
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
	unsigned int num, i, n;

    if (toolbox::file_exists(nome_pagina))
        pagina.open(nome_pagina, std::fstream::in);
    else
        exit(2);

    /* ler dados */
	pagina >> n;
    for (i = 0; i < n; ++i)
	{
		pagina >> pk >> num;
		dados.push_back(Node(pk, num));
	}

    /* ler filhas */
    pagina >> n;
    for (i = 0; i < n; ++i)
    {
        pagina >> num;
        filhas.push_back(num);
    }

	free(nome_pagina);
	pagina.close();
}

Pagina* Pagina::dividir_pagina()
{
	Pagina *outlet = new Pagina[5];
	unsigned int i;

	for (i = 0; i < dados.size()/2; ++i)
        outlet[0].dados.push_back(dados[i]);
    outlet[1].dados.push_back(dados[i]);
	for (++i; i < dados.size(); ++i)
		outlet[2].dados.push_back(dados[i]);

    dados.clear();
	return outlet;
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

Pagina::Pagina(unsigned int no)
{
    no_pagina = no;
    no_mae = -1;
    carregar_pagina();
}

Pagina* Pagina::achar_filha(Node no)
{
    unsigned int i;

    if (filhas.size() == 0)
        return this;
    for (i = 0; i < dados.size(); ++i)
    {
        // std::cout << dados[i].get_pk() << " x " << no.get_pk() << std::endl;
        if (dados[i].get_pk().compare(no.get_pk()) > 0)
            break;
    }
    Pagina filha(filhas[i]);
    filha.definir_mae(no_pagina);
    return filha.achar_filha(no);
}

void Pagina::adicionar(Node no)
{
    unsigned int i;

    toolbox::debug(("adding " + no.get_pk() + "...").c_str());
    if (dados.size() == 0)
        dados.push_back(no);
    else
    {
        std::cout << "dados.size() == " << this->dados.size() << std::endl;
        for (i = 0; i < dados.size(); ++i)
        {
            std::cout << "- " << dados[i].get_pk() << " x " << no.get_pk() << std::endl;
            if (dados[i].get_pk().compare(no.get_pk()) > 0)
                break;
        }
        std::cout << "for returned " << i << std::endl;
        dados.insert(dados.begin() + i, no);
    }
    salvar();
}

bool Pagina::overflow()
{
    return (dados.size() > TAMANHO_PAGINA);
}

Node Pagina::dividir_filhas()
{
	Pagina *paginas = dividir_pagina();
	Pagina menor = paginas[0];
	Pagina meio  = paginas[1];
	Pagina maior = paginas[2];

    // std::vector<Node>::iterator it;
    // std::cout << "menor:" << std::endl;
    // for (it = menor.dados.begin(); it != menor.dados.end(); ++it)
    //     std::cout << "  " << (*it).get_pk() << std::endl;
    // std::cout << "maior:" << std::endl;
    // for (it = maior.dados.begin(); it != maior.dados.end(); ++it)
    //     std::cout << "  " << (*it).get_pk() << std::endl;

	menor.definir_pagina(++NUMERO_PAGINA);
	menor.definir_mae(no_pagina);
	filhas.push_back(NUMERO_PAGINA);
	menor.salvar();

	maior.definir_pagina(++NUMERO_PAGINA);
	maior.definir_mae(no_pagina);
	filhas.push_back(NUMERO_PAGINA);
	maior.salvar();

	// menor.identificar();
	// maior.identificar();
    free(paginas);
	return meio.dados[0];
}

Pagina* Pagina::lidar_com_mae()
{
    /* esta página não tem uma mãe */
    // ela se torna a nova raiz
    /* caso contrário... */
    // retorne a mãe

    if (no_mae == (unsigned int) -1)
    {
        // std::cout << "i am my own mother" << std::endl;
        return this;
    }

    Pagina* mae = new Pagina();
    mae->definir_pagina(no_mae);
    return mae;
}

void Pagina::definir_pagina(unsigned int no)
{
    no_pagina = no;
    // carregar_pagina(); //?
}

void Pagina::definir_mae(unsigned int no)
{ no_mae = no; }

void Pagina::salvar()
{
    std::fstream pagina;
	char *nome_pagina = gerar_nome_pagina(no_pagina);
	std::vector<Node>::iterator dado;
    std::vector<unsigned int>::iterator filha;

	pagina.open(nome_pagina, std::fstream::out);

    pagina << dados.size() << std::endl;
	for (dado = dados.begin(); dado != dados.end(); ++dado)
        pagina << dado->pk << " " << dado->linha << std::endl;
    pagina << filhas.size() << std::endl;
    for (filha = filhas.begin(); filha != filhas.end(); ++filha)
        pagina << *filha << std::endl;

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
