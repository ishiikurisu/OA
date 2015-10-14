#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

class OrdenadorIndices{
	std::vector<std::string> preencher_do_arquivo(std::string);
	void escrever_para_arquivo(std::string, std::vector<std::string>);
public:
	OrdenadorIndices (void){};
	void ordenar (std::string);
};

/*
* FUNCOES PRIVADAS
*/
std::vector<std::string> OrdenadorIndices::preencher_do_arquivo(std::string input)
{
	std::fstream inlet;
	std::vector<std::string> outlet;
	std::string line;

	inlet.open(input.c_str(), std::fstream::in);
	for (std::getline(inlet, line); line.length() > 0; std::getline(inlet, line))
		outlet.push_back(line);

	inlet.close();
	return outlet;
}

void OrdenadorIndices::escrever_para_arquivo(std::string path, std::vector<std::string> in)
{
	std::fstream outlet;
	std::vector<std::string>::iterator it;

	outlet.open(path.c_str(), std::fstream::in);
	for (it = in.begin(); it != in.end(); ++it)
		outlet << *it << std::endl;
	outlet.close();
}

/*
* FUNCOES PUBLICAS
*/
void OrdenadorIndices::ordenar (std::string endereco)
{
	std::vector<std::string> chaves = preencher_do_arquivo(endereco);
	std::sort(chaves.begin(), chaves.end()); // CHEATING
	escrever_para_arquivo(endereco, chaves);
}
