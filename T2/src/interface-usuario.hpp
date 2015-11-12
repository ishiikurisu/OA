#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <btree.hpp>
#include <toolbox.hpp>

class InterfaceUsuario
{
	void adicionar();
	void buscar();
	BTree btree;
	char *caminho;
public:
	InterfaceUsuario() {};
	void setup();
	bool draw();
};

void InterfaceUsuario::setup()
{
	std::fstream arquivo;
	std::string linha;

	caminho = (char*) malloc(sizeof(char) * 11);
	caminho = "lista.txt";
	arquivo.open(caminho, std::fstream::in);

	std::cout << "# Arquivo original" << std::endl;
	std::getline(arquivo, linha);
	while (linha.length() > 1)
	{
		std::cout << "+ " << linha << std::endl;
		btree.adicionar(linha);
		std::getline(arquivo, linha);
	}

	arquivo.close();
}

bool InterfaceUsuario::draw()
{
	bool permaneca = true;
	std::string junk;

	std::cout << "# Selecione uma opcao" << std::endl;
	std::cout << "0. Sair" << std::endl;
	std::cout << "1. Buscar" << std::endl;
	std::cout << "2. Adicionar" << std::endl;
	std::getline(std::cin, junk);

	switch (toolbox::str2num(junk.c_str())) {
		case 0:
			permaneca = false;
			std::cout << "Obrigado por usar a aplicacao :)" << std::endl;
			std::getline(std::cin, junk);
		break;

		// case 1:
		// 	buscar();
		// break;
		//
		// case 2:
		// 	adicionar();
		// break;

		default:
			std::cout << "Opção não implementada" << std::endl;
			std::getline(std::cin, junk);
	}

	return permaneca;
}

/*******************
* FUNÇÕES PRIVADAS *
*******************/
void InterfaceUsuario::buscar()
{

}

void InterfaceUsuario::adicionar()
{

}
