#ifndef PROCURAR_HPP
#define PROCURAR_HPP
#include <string>
#include <fstream>
#include <iostream>

class Procurador
{
	std::string tratar_linha(std::string);
public:
	Procurador() {};
	std::string procurar(std::string, std::string);
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/
std::string Procurador::tratar_linha(std::string linha)
{
	std::string saida;

	for (int c = 7; c < 48 ; c++)
		saida += linha[c];

	return saida;
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/
std::string Procurador::procurar(std::string nome_arquivo, std::string agulha)
{
	std::fstream palheiro;
	std::string linha;

	for (palheiro.open(nome_arquivo, std::fstream::in), std::getline(palheiro, linha);
         linha.length() > 1;
	     std::getline(palheiro, linha))
	{
		if (linha.find(agulha) < linha.length()) {
			palheiro.close();
			return tratar_linha(linha);
		}
	}

	palheiro.close();
	return std::string("");
}

#endif /* end of include guard: PROCURAR_HPP */
