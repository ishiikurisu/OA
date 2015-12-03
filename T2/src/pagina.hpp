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
    std::vector<Node> dados;
    std::vector<unsigned int> filhas;
    Pagina *nova_mae;
public:
    Pagina() { no_mae = -1; };
    Pagina(unsigned int);
    ~Pagina() { };
    Pagina* achar_filha(Node);
    unsigned int adicionar(Node);
    bool overflow();
    Node dividir(Node);
    Pagina *atualizar();
    void salvar();
    std::string escrever();
    std::string identificar();
    unsigned int no_pagina;
    unsigned int no_mae;
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

    pagina >> no_mae;

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

    delete nome_pagina;
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

Pagina::Pagina(unsigned int no) : Pagina::Pagina()
{
    no_pagina = no;
    carregar_pagina();
}

Pagina* Pagina::achar_filha(Node no)
{
    unsigned int i;

    if (filhas.size() == 0)
        return this;
    for (i = 0; i < dados.size(); ++i)
    {
        if (dados[i].get_pk().compare(no.get_pk()) > 0)
            break;
    }
    Pagina *filha = new Pagina(filhas[i]);
    filha->no_mae = no_pagina;
    return filha->achar_filha(no);
}

unsigned int Pagina::adicionar(Node no)
{
    unsigned int i = 0;

    if (dados.size() == 0)
        dados.push_back(no);
    else
    {
        for (i = 0; i < dados.size(); ++i)
            if (dados[i].get_pk().compare(no.get_pk()) > 0)
                break;
        dados.insert(dados.begin() + i, no);
    }

    salvar();
    return i;
}

bool Pagina::overflow()
{
    return (dados.size() > TAMANHO_PAGINA);
}

Node Pagina::dividir(Node no)
{
    Pagina *paginas = dividir_pagina();
    Pagina *mae = this;
    unsigned int where = -1;
    Pagina menor = paginas[0];
    Pagina meio  = paginas[1];
    Pagina maior = paginas[2];

    /* dividir filhas */
    menor.no_pagina = ++NUMERO_PAGINA;
    menor.no_mae = no_pagina;

    maior.no_pagina = ++NUMERO_PAGINA;
    maior.no_mae = no_pagina;

    /* lidar com mãe */
    no = meio.dados[0];
    if (no_mae == (unsigned int) -1)
    {
        where = adicionar(no);
        filhas.insert(filhas.begin() + where++, NUMERO_PAGINA-1);
        filhas.insert(filhas.begin() + where, NUMERO_PAGINA);
    }
    else
    {
        mae = new Pagina(no_mae);
        // erase current daughter
        where = toolbox::encontrar(mae->filhas, no_pagina);
        mae->filhas.erase(mae->filhas.begin() + where);
        // add new daughters
        mae->adicionar(no);
        mae->filhas.insert(mae->filhas.begin() + where++, NUMERO_PAGINA-1);
        mae->filhas.insert(mae->filhas.begin() + where, NUMERO_PAGINA);
    }

    menor.no_mae = mae->no_pagina;
    menor.salvar();

    maior.no_mae = mae->no_pagina;
    maior.salvar();

    mae->salvar();
    nova_mae = mae;
    delete paginas;
    return meio.dados[0];
}

Pagina* Pagina::atualizar()
{
    return nova_mae;
}

void Pagina::salvar()
{
    std::fstream pagina;
    char *nome_pagina = gerar_nome_pagina(no_pagina);
    std::vector<Node>::iterator dado;
    std::vector<unsigned int>::iterator filha;

    pagina.open(nome_pagina, std::fstream::out);

    pagina << no_mae << std::endl;
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

/* code is poetry */
