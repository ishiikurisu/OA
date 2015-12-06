#pragma once
#include <iostream>
#include <fstream>
#include <btree.hpp>
#include <stdio.h>

class Banco
{
	std::string gerar_chave(std::string);
	std::string pegar(unsigned int);
	std::string arquivo_principal;
	BTree btree;
	unsigned int no_dados;
	unsigned int ultima_pesquisa;
public:
	Banco();
	void definir_arquivo_principal(std::string);
	void popular(std::string);
	void adicionar(std::string);
	void atualizar(std::string);
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
	std::string linha;
	std::fstream arquivo;

	arquivo.open(arquivo_principal.c_str(), std::fstream::in);
	for (unsigned int c = 0; c < no_linha; c++)
		std::getline(arquivo, linha);

	arquivo.close();
	ultima_pesquisa = no_linha;
	return linha;
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
	std::ofstream fs;

	fs.open(arquivo_principal.c_str(), std::ios_base::app);
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

void Banco::atualizar(std::string pesquisa)
{
	std::string TEMP = "TEMP";
	std::string linha;
	std::fstream arquivo;
	std::fstream temp;
	unsigned int c;

	arquivo.open(arquivo_principal.c_str(), std::fstream::in);
	temp.open(TEMP.c_str(), std::fstream::out);

	for (c = 0; c < ultima_pesquisa-1; c++)
	{
		std::getline(arquivo, linha);
		temp << linha << std::endl;
	}
	std::getline(arquivo, linha);
	temp << pesquisa << std::endl;
	for (c++; c < no_dados; c++)
	{
		std::getline(arquivo, linha);
		temp << linha << std::endl;
	}

	arquivo.close();
	temp.close();
	remove(arquivo_principal.c_str());
	rename(TEMP.c_str(), arquivo_principal.c_str());
}

void Banco::mostrar()
{
	btree.mostrar();
}
