#ifndef ADICIONAR_INDICES_HPP
#define ADICIONAR_INDICES_HPP
#include <fstream>
#include <vector>
#include <criador-indices-primario.hpp>

class AdicionadorIndices
{
	int contar_linhas();
	void escrever_dados(std::vector<std::string>);
	std::fstream fs;
public:
	AdicionadorIndices() {};
	void adicionar(std::string, std::vector<std::string>);
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

int AdicionadorIndices::contar_linhas()
{
	int c = 0;
	std::string linha;
	for (std::getline(fs, linha);
	     linha.length() > 0;
		 std::getline(fs, linha), c++);
	fs.seekg(0, fs.beg);
	return c;
}

void AdicionadorIndices::escrever_dados(std::vector<std::string> dados)
{
	std::string dado;
	size_t i = 0;

	/* matricula */
	for (i = 0; dados[0][i] == ' '; ++i)
	fs << dados[0] << " ";

	/* nome */
	dado = dados[1];
	if (dado.length() > 40) {
		for (i = 0; i < 40; ++i)
			fs << dado.at(i);
	}
	else {
		fs << dado;
		for (i = 0; i < 40 - dado.length(); ++i)
			fs << " ";
	}
	fs << " ";

	/* op */
	fs << dados[2] << " ";

	/* curso */
	dado = dados[3];
	if (dado.length() > 8) {
		for (i = 0; i < 8; ++i)
			fs << dado.at(i);
	}
	else {
		fs << dado;
		for (i = 0; i < 8 - dado.length(); ++i)
			fs << " ";
	}
	fs << " ";

	/* turma */
	fs << dados[4] << std::endl;
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/
void AdicionadorIndices::adicionar(std::string entrada,
	                               std::vector<std::string> dados)
{
	int i;
	std::string chave;
	std::string junk;
	// CriadorIndicesPrimario cip;
	// CriadorIndicesSecundario cis;

	/* lidar com arquivo de dados */
	fs.open(entrada.c_str());
	fs.seekg(0, fs.end);
	escrever_dados(dados);
	fs.close();

	/* lidar com arquivo de chaves primárias */
	// fs.open(cip.gerar_saida(entrada));
	// chave = cip.gerar_chave();
	// fs.close();

	/* lidar com arquivo de chaves secundarias */
	// fs.open(cis.gerar_saida());
	// chave = cis.gerar_chave();
	// fs.close();
}

#endif /* end of include guard: ADICIONAR_INDICES_HPP */
