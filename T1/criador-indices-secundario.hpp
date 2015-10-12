#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>

class CriadorIndicesSecundario {
private:
	std::string gerar_saida(std::string);
	std::string gerar_chave (std::string);
public:
	CriadorIndicesSecundario(void) {};
	std::string gerar_indices(std::string);
};

std::string CriadorIndicesSecundario::gerar_saida(std::string endereco)
{
	std::string saida;
	size_t i = 0;

	saida = "indice";
	for (; i < endereco.length() && endereco.at(i) != '/'; ++i)
		;
	for (++i; i < endereco.length() && endereco.at(i) != '.'; ++i)
		saida += endereco.at(i);

	saida += ".sec";
	std::cout << "\t" << saida << std::endl;
	return saida;

}

std::string CriadorIndicesSecundario::gerar_chave(std::string linha)
{
	std::string saida;
	int count;
	for (count=52; count<=53; count++)
	{
		saida+=linha[count];
	}
	std::cout << saida << std::endl;
	return saida;
}


std::string CriadorIndicesSecundario::gerar_indices(std::string endereco)
{
	std::string saida = gerar_saida(endereco);
	std::string linha;
	std::fstream inlet; // arquivo de listas
	std::fstream outlet;  //arquivos de indices secundarios

	inlet.open(endereco.c_str(), std::fstream::in);
	prima.open(saida.c_str(), std::fstream::out);

	/* gerar índice primário */
	std::getline(inlet, linha);
	for (size_t cont = 1; linha.length() > 1; ++cont, std::getline(inlet, linha))
	{
		outlet << gerar_chave(linha) << " " << cont << std::endl;
	}

	inlet.close();
	outlet.close();
	return saida;
}
