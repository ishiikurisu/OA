#ifndef ATUALIZAR_INDICES_HPP
#define ATUALIZAR_INDICES_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define TEMP ("saida.temp")

class AtualizadorIndices
{
	void atualizar_arquivo_principal(std::string, std::vector<std::string>, std::vector<std::string>);
	void atualizar_arquivo_chaves(std::string, std::vector<std::string>, std::vector<std::string>);
public:
	AtualizadorIndices() {};
	void atualizar(std::string, std::vector<std::string>, std::vector<std::string>);
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/
void AtualizadorIndices::atualizar_arquivo_principal(std::string nome_arquivo,
	                               std::vector<std::string> antigos,
								   std::vector<std::string> novos)
{
	std::fstream inlet;
	std::fstream outlet;
	std::string matricula_antiga;
	std::string nome_antigo;
	std::string matricula_nova;
	std::string nome_novo;
	std::string linha;
	size_t i;

	inlet.open(nome_arquivo.c_str(), std::fstream::in);
	outlet.open(TEMP, std::fstream::out);
	matricula_antiga = antigos[0];
	nome_antigo = antigos[1];
	matricula_nova = (novos[0].length() > 1)? novos[0] : matricula_antiga;
	nome_novo = (novos[1].length() > 1)? novos[1] : nome_antigo;

	for (std::getline(inlet, linha); linha.length() > 1; std::getline(inlet, linha))
	{
		if (linha.find(matricula_antiga) < linha.length()) {
			outlet << matricula_nova << " ";
			outlet << nome_novo;
			for (i = nome_novo.length(); i <= 40; ++i)
				outlet << " ";
			for (i = 49; i < linha.length(); ++i)
				outlet << linha.at(i);
			outlet << std::endl; // substring inalterada da linha
		}
		else {
			outlet << linha << std::endl;
		}
	}

	inlet.close();
	outlet.close();
	remove(nome_arquivo.c_str());
	rename(TEMP, nome_arquivo.c_str());
}

#include <criador-indices-primario.hpp>
void AtualizadorIndices::atualizar_arquivo_chaves(std::string nome_arquivo,
	                               std::vector<std::string> antigos,
								   std::vector<std::string> novos)
{
	std::fstream inlet;
	std::fstream outlet;
	std::string matricula_antiga;
	std::string nome_antigo;
	std::string matricula_nova;
	std::string nome_novo;
	std::string chave_nova;
	std::string linha;
	CriadorIndicesPrimario cip;
	size_t i;

	inlet.open(cip.gerar_saida(nome_arquivo).c_str(), std::fstream::in);
	outlet.open(TEMP, std::fstream::out);
	matricula_antiga = antigos[0];
	nome_antigo = antigos[1];
	matricula_nova = (novos[0].length() > 0)? novos[0] : matricula_antiga;
	nome_novo = (novos[1].length() > 0)? novos[1] : nome_antigo;
	chave_nova = cip.gerar_chave(matricula_nova + " " + nome_novo + "          ");

	for (std::getline(inlet, linha); linha.length() > 1; std::getline(inlet, linha))
	{
		if (linha.find(matricula_antiga) < linha.length()) {
			outlet << chave_nova << " ";
			for (i = chave_nova.length(); i < linha.length(); ++i)
				outlet << linha.at(i);
			outlet << std::endl;
		}
		else {
			outlet << linha << std::endl;
		}
	}

	inlet.close();
	outlet.close();
	remove(cip.gerar_saida(nome_arquivo).c_str());
	rename(TEMP, cip.gerar_saida(nome_arquivo).c_str());
}

/*******************
* FUNÇÕES PUBLICAS *
*******************/

void AtualizadorIndices::atualizar(std::string nome_arquivo,
	                               std::vector<std::string> antigos,
								   std::vector<std::string> novos)
{
	atualizar_arquivo_principal(nome_arquivo, antigos, novos);
	atualizar_arquivo_chaves(nome_arquivo, antigos, novos);
}

#endif /* end of include guard: ATUALIZAR_INDICES_HPP */
