#ifndef EXCLUIR_INDICES_HPP
#define EXCLUIR_INDICES_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <criador-indices-primario.hpp>
#define ARQTEMP ("saida.temp")

class ApagadorIndices
{
	bool encontrar(std::string, std::string);
	void apagar_no_arquivo(std::string, std::string);
public:
	ApagadorIndices() {};
	void excluir(std::string, std::string);
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

bool ApagadorIndices::encontrar(std::string palheiro, std::string agulha)
{
	return (palheiro.find(agulha) < palheiro.length())? true : false;
}

void ApagadorIndices::apagar_no_arquivo(std::string nome_arquivo, std::string matricula) {
	std::fstream arquivo;
	std::fstream saida;
	std::string linha;

	arquivo.open(nome_arquivo.c_str(), std::fstream::in);
	saida.open(ARQTEMP, std::fstream::out);

	for (std::getline(arquivo, linha); linha.length() > 1; std::getline(arquivo, linha))
		if (!encontrar(linha, matricula))
			saida << linha << std::endl;

	arquivo.close();
	saida.close();
	remove(nome_arquivo.c_str());
	rename(ARQTEMP, nome_arquivo.c_str());
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

void ApagadorIndices::excluir(std::string arquivo, std::string matricula) {
	CriadorIndicesPrimario cip;

	apagar_no_arquivo(arquivo, matricula);
	apagar_no_arquivo(cip.gerar_saida(arquivo), matricula);
}

#undef ARQTEMP
#endif /* end of include guard: EXCLUIR_INDICES_HPP */
