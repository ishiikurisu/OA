#pragma once
#include <iostream>
#include <fstream>
#include <btree.hpp>

class Banco
{
	std::string gerar_chave(std::string);
	std::string arquivo_principal;
	std::string arquivo_chaves;
	BTree btree;
	unsigned int no_dados;
public:
	Banco();
	void definir_arquivo_principal(std::string);
	void popular(std::string);
	void adicionar(std::string);
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
	for (i = 8; i < 12; ++i)
		chave += linha.at(i);

	return chave;
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

Banco::Banco()
{
	arquivo_chaves = "indicelista.bt";
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

	popular(dado);
	fs.close();
}

void Banco::mostrar()
{
	btree.mostrar();
}
