#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <banco.hpp>
#include <toolbox.hpp>

class InterfaceUsuario
{
	void adicionar();
	void buscar();
	Banco banco;
	std::string caminho;
public:
	InterfaceUsuario() {};
	void setup();
	bool draw();
};

void InterfaceUsuario::setup()
{
	std::fstream arquivo;
	std::string linha;

	caminho = "lista.txt";
	arquivo.open(caminho.c_str(), std::fstream::in);

	std::cout << "# Arquivo original" << std::endl;
	std::getline(arquivo, linha);
	while (linha.length() > 1)
	{
		std::cout << "+ " << linha << std::endl;
		banco.popular(linha);
		std::getline(arquivo, linha);
	}

	banco.definir_arquivo_principal(caminho);
	banco.mostrar();
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
		case 2:
			adicionar();
		break;

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
	std::string info;
	std::string linha;
	int a;

	std::cout << "--- # Adicionar" << std::endl;

	std::cout << "Matricula do aluno:" << std::endl;
	std::getline(std::cin, linha);
	info += linha + " ";

	std::cout << "Nome:" << std::endl;
	std::getline(std::cin, linha);
	if (linha.length() < 40)
		for (a = linha.length(); a < 40; linha += ' ', ++a);
	info += linha + " ";

	std::cout << "Opção:" << std::endl;
	std::getline(std::cin, linha);
	if (linha.length() < 3)
		for (a = linha.length(); a < 3; linha += ' ', ++a);
	info += linha + " ";

	std::cout << "Curso:" << std::endl;
	std::getline(std::cin, linha);
	if (linha.length() < 8)
		for (a = linha.length(); a < 8; linha += ' ', ++a);
	info += linha + " ";

	std::cout << "Turma:" << std::endl;
	std::getline(std::cin, linha);
	info += linha;

	std::cout << "..." << std::endl;
	banco.adicionar(info);
}
