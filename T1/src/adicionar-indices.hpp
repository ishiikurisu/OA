#ifndef ADICIONAR_INDICES_HPP
#define ADICIONAR_INDICES_HPP
#include <fstream>
#include <vector>
#include <criador-indices-primario.hpp>

class AdicionadorIndices
{
	int contar_linhas();
	std::string gerar_chave(std::vector<std::string>);
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

std::string AdicionadorIndices::gerar_chave(std::vector<std::string> dados)
{
	std::string saida;
	std::string dado;
	size_t i = 0;

	/* matricula */
	saida += dados[0] + " ";

	/* nome */
	dado = dados[1];
	if (dado.length() > 40) {
		for (i = 0; i < 40; ++i)
			saida += dado.at(i);
	}
	else {
		saida += dado;
		for (i = dado.length(); i < 40; ++i)
			saida += " ";
	}
	saida += " ";

	/* op */
	saida += dados[2] + "  ";

	/* curso */
	dado = dados[3];
	if (dado.length() > 8) {
		for (i = 0; i < 8; ++i)
			saida += dado.at(i);
	}
	else {
		saida += dado;
		for (i = dado.length(); i < 8; ++i)
			saida += " ";
	}
	saida += " ";

	/* turma */
	saida += dados[4];

	return saida;
}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/
void AdicionadorIndices::adicionar(std::string entrada,
	                               std::vector<std::string> dados)
{
	std::string chave;
	CriadorIndicesPrimario cip;
	OrdenadorIndices oi;
	// CriadorIndicesSecundario cis;

	chave = gerar_chave(dados);

	/* lidar com arquivo de dados */
	fs.open(entrada.c_str());
	fs.seekg(0, fs.end);
	fs << chave << std::endl;
	fs.close();
	oi.ordenar_roubando(entrada);

	/* lidar com arquivo de chaves primárias */
	entrada = cip.gerar_saida(entrada);
	fs.open(entrada.c_str());
	chave = cip.gerar_chave(chave);
	fs.seekg(0, fs.end);
	fs << chave << std::endl;
	fs.close();
	oi.ordenar_roubando(entrada);

	/* lidar com arquivo de chaves secundarias */
	// fs.open(cis.gerar_saida(entrada).c_str());
	// chave = cis.gerar_chave(chave);
	// fs.close();
}

#endif /* end of include guard: ADICIONAR_INDICES_HPP */
