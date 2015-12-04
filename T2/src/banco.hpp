#pragma once
#include <iostream>
#include <fstream>
#include <btree.hpp>

class Banco
{
	std::string gerar_chave(std::string);
	std::string pegar(unsigned int)
	std::string arquivo_principal;
	BTree btree;
	unsigned int no_dados;
public:
	Banco();
	void definir_arquivo_principal(std::string);
	void popular(std::string);
	void adicionar(std::string);
	std::string buscar(std::string);
	void mostrar();
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

std::string Banco::gerar_chave(std::string linha)
{
	std::string chave;
	int i;

	for (i = 0; i < 6; ++i)
		chave += linha.at(i);
	for (i = 7; i < 11; ++i)
		chave += linha.at(i);

	return chave;
}

std::string Banco::pegar(unsigned int no_linha)
{
	return std::string("");
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

Banco::Banco()
{
	no_dados = 0;
}

void Banco::definir_arquivo_principal(std::string nome)
{
	arquivo_principal = nome;
}

void Banco::popular(std::string dado)
{
	btree.adicionar(gerar_chave(dado), ++no_dados);
}

void Banco::adicionar(std::string dado)
{
	std::fstream fs;

	fs.open(arquivo_principal.c_str(), std::fstream::in);
	fs.seekg(0, fs.end);
	fs << dado << std::endl;
	fs.close();

	popular(dado);
}

std::string Banco::buscar(std::string pedido)
{
	unsigned int linha = btree.buscar(pedido);

	if (linha == (unsigned int) -1)
		return std::string("");
	else
		return pegar(linha);
}

void Banco::mostrar()
{
	btree.mostrar();
}
