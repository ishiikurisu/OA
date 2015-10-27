#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>

class CriadorIndicesSecundario {
private:
	std::string itos(size_t);
	std::string gerar_saida(std::string);
	std::string gerar_chave (std::string, size_t);
	std::map<std::string, size_t> led;
public:
	CriadorIndicesSecundario(void) {};
	std::string gerar_indices(std::string);
};

std::string CriadorIndicesSecundario::gerar_saida(std::string endereco)
{
	std::string saida;

	for (size_t i = 0; i < endereco.length() && endereco.at(i) != '.'; ++i)
		saida += endereco.at(i);

	saida += ".sec";
	// std::cout << "# " << saida << ":" << std::endl;
	return saida;

}

std::string CriadorIndicesSecundario::itos(size_t n)
{
	char s[256];
	std::string r;
	sprintf(s, "%d", n);
	r += s;
	return r;
}

std::string CriadorIndicesSecundario::gerar_chave(std::string linha, size_t no_linha)
{
	std::string saida;

	for (int count = 16; count < 18; count++)
		saida += linha[count];

	// std::cout << "  \'" << saida << "\'" << std::endl;
	if (led.count(saida)) {
		size_t temp = led[saida];
		led[saida] = no_linha;
		saida += " " + itos(temp);
	}
	else {
		led[saida] = no_linha;
		saida += " -1";
	}

	return saida;
}


std::string CriadorIndicesSecundario::gerar_indices(std::string endereco)
{
	std::string saida = gerar_saida(endereco);
	std::string linha;
	std::fstream inlet; // arquivo de listas
	std::fstream outlet;  //arquivos de indices secundarios

	inlet.open(endereco.c_str(), std::fstream::in);
	outlet.open(saida.c_str(), std::fstream::out);

	/* gerar índice primário */
	std::getline(inlet, linha);
	for (size_t cont = 1; linha.length() > 1; ++cont, std::getline(inlet, linha))
	{
		outlet << gerar_chave(linha, cont) << std::endl;
	}

	inlet.close();
	outlet.close();
	led.clear();
	return saida;
}
