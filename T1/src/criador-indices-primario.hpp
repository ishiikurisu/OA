#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>

class CriadorIndicesPrimario {
private:
	std::string gerar_saida(std::string);
	std::string gerar_chave(std::string);

public:
	CriadorIndicesPrimario(void) {};
	std::string gerar_indices(std::string);
};

std::string CriadorIndicesPrimario::gerar_saida(std::string endereco)
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

std::string CriadorIndicesPrimario::gerar_chave(std::string linha)
{
	std::string saida;
	int count;
	for (count=0; count<=5; count++)
	{
		saida+=linha[count];
	}
	for (count++; count<=15; count++)
	{
		saida+=linha[count];
	}
	std::cout << saida << std::endl;
	return saida;
}

std::string CriadorIndicesPrimario::gerar_indices(std::string endereco)
{
	std::string saida = gerar_saida(endereco);
	std::string linha;
	std::fstream inlet; // arquivo de listas
	std::fstream outlet;  //arquivos de indices primarios

	inlet.open(endereco.c_str(), std::fstream::in);
	outlet.open(saida.c_str(), std::fstream::out);

	/* gerar índice primário */
	std::getline(inlet, linha);
	for (size_t cont = 1; linha.length() > 1; ++cont, std::getline(inlet, linha))
	{
		outlet << gerar_chave(linha) << std::endl;
	}

	inlet.close();
	outlet.close();
	return saida;
}
