#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>

class CriadorIndices {
private:
	std::string gerar_saida(std::string);
public:
	CriadorIndices(void) {};
	std::string gerar_indices(std::string);
};

std::string CriadorIndices::gerar_saida(std::string endereco)
{
	std::string saida;
	size_t i = 0;

	saida = "indice";
	for (; i < endereco.length() && endereco.at(i) != '/'; ++i)
		;
	for (++i; i < endereco.length() && endereco.at(i) != '.'; ++i)
		saida += endereco.at(i);

	saida += ".ind";
	std::cout << "\t" << saida << std::endl;
	return saida;
}

std::string CriadorIndices::gerar_indices(std::string endereco)
{
	std::string saida = gerar_saida(endereco);
	std::fstream inlet;
	std::fstream outlet;

	inlet.open(endereco.c_str(), std::fstream::in);
	outlet.open(saida.c_str(), std::fstream::out);

	while (/* ler linhas */0)
	{
		/* gera índice */
		/* escreve no arquivo de índices */
	}

	inlet.close();
	outlet.close();
	return saida;
}
