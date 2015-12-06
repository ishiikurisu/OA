#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <banco.hpp>
#include <toolbox.hpp>
#define CAMINHO ("lista.txt")

class InterfaceUsuario
{
	void adicionar();
	void buscar();
	void atualizar();
	Banco banco;
public:
	InterfaceUsuario() {};
	void setup();
	bool draw();
};

void InterfaceUsuario::setup()
{
	std::fstream arquivo;
	std::string linha;

	arquivo.open(CAMINHO, std::fstream::in);

	// std::cout << "# Arquivo original" << std::endl;
	std::getline(arquivo, linha);
	while (linha.length() > 1)
	{
		// std::cout << "+ " << linha << std::endl;
		banco.popular(linha);
		std::getline(arquivo, linha);
	}

	banco.definir_arquivo_principal(CAMINHO);
	banco.mostrar();
	arquivo.close();
}

bool InterfaceUsuario::draw()
{
	bool permaneca = true;
	std::string junk;

	std::cout << "--- # Selecione uma opcao" << std::endl;
	std::cout << "0. Sair" << std::endl;
	std::cout << "1. Buscar" << std::endl;
	std::cout << "2. Adicionar" << std::endl;
	std::cout << "3. Atualizar" << std::endl;
	std::getline(std::cin, junk);

	switch (toolbox::str2num(junk.c_str())) {
		case 0:
			permaneca = false;
			std::cout << "Obrigado por usar a aplicacao :)" << std::endl;
		break;

		case 1:
			buscar();
		break;

		case 2:
			adicionar();
			banco.mostrar();
		break;

		case 3:
			atualizar();
			banco.mostrar();
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
	std::string texto;

	std::cout << "--- # Buscar" << std::endl;
	std::cout << "Matricula do aluno" << std::endl;
	std::getline(std::cin, texto);

	texto = banco.buscar(texto);
	if (texto.length() == 0) {
		std::cout << "Matrícula não encontrada" << std::endl;
	}
	else {
		std::cout << "Resultado da busca:" << std::endl;
		std::cout << "- " << texto << std::endl;
	}
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

void InterfaceUsuario::atualizar()
{
	std::string matricula;
	std::string pesquisa;
	std::string atualizacao;
	std::string info;

	std::cout << "--- # Atualizar" << std::endl;
	std::cout << "Matricula do aluno:" << std::endl;
	std::getline(std::cin, matricula);
	pesquisa = banco.buscar(matricula);

	if (pesquisa.length() > 0) {
		std::cout << "Dados encontrados:" << std::endl;
		std::cout << "- " << pesquisa << std::endl;
		std::cout << "# Deixe o campo em branco ";
		std::cout << "para manter o mesmo dado" << std::endl;

		atualizacao = matricula + " ";
		std::cout << "Nome:" << std::endl;
		std::getline(std::cin, info);
		atualizacao += (info.length() == 0)?
		 	pesquisa.substr(8, 40) : toolbox::preencher(info, 40);
		atualizacao += " ";
		std::cout << "Opcao:" << std::endl;
		std::getline(std::cin, info);
		atualizacao += (info.length() == 0)?
		 	pesquisa.substr(49, 3) : toolbox::preencher(info, 3);
		atualizacao += " ";
		std::cout << "Curso:" << std::endl;
		std::getline(std::cin, info);
		atualizacao += (info.length() == 0)?
		 	pesquisa.substr(53, 8) : toolbox::preencher(info, 8);
		atualizacao += " ";
		std::cout << "Turma:" << std::endl;
		std::getline(std::cin, info);
		atualizacao += (info.length() == 0)?
		 	pesquisa.substr(62, 1) : toolbox::preencher(info, 1);

		banco.atualizar(atualizacao);
	}
	else {
		std::cout << "Matricula nao encontrada" << std::endl;
	}
}

#undef CAMINHO
