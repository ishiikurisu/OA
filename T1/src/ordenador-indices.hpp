#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

class OrdenadorIndices{
	std::vector<std::string> preencher_do_arquivo(std::string);
	std::vector<std::string> heapsort(std::vector<std::string>);
	void escrever_para_arquivo(std::string, std::vector<std::string>);
	bool comparar(std::string, std::string);
	std::vector<std::string> desmontar(std::vector<std::string>);
public:
	OrdenadorIndices(void) {};
	void ordernar_roubando(std::string);
	void ordenar(std::string);
};

/*******************
* FUNCOES PRIVADAS *
*******************/
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

bool OrdenadorIndices::comparar(std::string s, std::string t)
{
	return (s.compare(t) > 0);
}

std::vector<std::string> OrdenadorIndices::desmontar(std::vector<std::string> inlet)
{
// 	std::vector<std::string> outlet;
// 	std::vector<std::string>::iterator it;
//
// 	for ()
//
//
// 	return outlet;
//
	return inlet;
}

/* implementação do heapsort como descrita por Folk, pg 170 do pdf */
std::vector<std::string> OrdenadorIndices::heapsort(std::vector<std::string> chaves)
{
	std::vector<std::string> heapArray;
	std::vector<std::string>::iterator it;
	int num, k;

	for (it = chaves.begin(); it != chaves.end(); ++it)
	{
		heapArray.push_back(*it);
		k=heapArray.size()-1;

		while(k>0)
		{
			num=k/2;
			if(!comparar(heapArray[k], heapArray[num]))
			{
				std::cout << "change" << std::endl;
				std::string array = heapArray[k];
				heapArray[k] = heapArray[num];
				heapArray[num] = array;
			}
			k=num;
		}

	}

	return heapArray;
}

/*******************
* FUNCOES PUBLICAS *
*******************/

void OrdenadorIndices::ordernar_roubando(std::string endereco)
{
	std::vector<std::string> chaves = preencher_do_arquivo(endereco);
	std::sort(chaves.begin(), chaves.end()); // CHEATING
	escrever_para_arquivo(endereco, chaves);
}

void OrdenadorIndices::ordenar (std::string endereco)
{
	escrever_para_arquivo(endereco, heapsort(preencher_do_arquivo(endereco)));
}
