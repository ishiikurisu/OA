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
    void mostrar(Pagina*);
public:
    BTree();
    void adicionar(std::string, unsigned int);
    void adicionar(Node);
    void mostrar();
    friend class Pagina;
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

void BTree::mostrar(Pagina* pagina)
{
    std::cout << "pagina: " << pagina->no_pagina << std::endl;
    std::cout << "dados:" << std::endl;
    if (pagina->filhas.size() > 0)
    {
        std::cout << "filhas:" << std::endl;
        for (std::vector<unsigned int> filha = pagina->filhas.size();
             )
    }
    std::cout << std::endl;
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

BTree::BTree()
{
    raiz.definir_pagina(1);
    raiz.definir_mae(-1);
}

void BTree::adicionar(Node no)
{
    Pagina *filha = raiz.achar_filha(no);
    filha->adicionar(no);

    while (filha->overflow())
    {
        no = filha->dividir_filhas();
        filha = filha->lidar_com_mae();
        filha->adicionar(no);
    }
}

void BTree::adicionar(std::string dado, unsigned int no_linha)
{
    adicionar(Node(dado, no_linha));
}

void BTree::mostrar()
{
    std::cout << "--- # BTREE" << std::endl;
    this->mostrar(&raiz);
    std::cout << "..." << std::endl;
}

#endif /* end of include guard: BTREE_H */
