#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>

class CriadorIndices {
private:
	std::string gerar_saida(std::string);
	std::string gerar_chave_primaria(std::string);
	std::string gerar_saida_secundaria (std::string);
	std::string gerar_chave_secundaria (std::string);
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

std::string CriadorIndices::gerar_saida_secundaria(std::string endereco)
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

std::string CriadorIndices::gerar_chave_primaria(std::string linha)
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

std::string CriadorIndices::gerar_chave_secundaria(std::string linha)
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


std::string CriadorIndices::gerar_indices(std::string endereco)
{
	std::string saida = gerar_saida(endereco);
	std::string ssec = gerar_saida_secundaria(endereco);
	std::string linha;
	std::fstream inlet; // arquivo de listas
	std::fstream prima;  //arquivos de indices primarios
	std::fstream secun;  //arquivos de indices secundarios

	inlet.open(endereco.c_str(), std::fstream::in);
	prima.open(saida.c_str(), std::fstream::out);
	secun.open(ssec.c_str(), std::fstream::out);

	/* gerar índice primário */
	std::getline(inlet, linha);
	for (size_t cont = 1; linha.length() > 1; ++cont, std::getline(inlet, linha))
	{
		/* gerar índice primario */
		prima << gerar_chave_primaria(linha) << " " << cont << std::endl;
		//gerar indice secundario
		secun << gerar_chave_secundaria(linha) << " " << cont << std::endl;
	}

	inlet.close();
	prima.close();
	secun.close();
	return saida;
}
