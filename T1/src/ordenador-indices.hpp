#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

class OrdenadorIndices{
	std::vector<std::string> preencher_do_arquivo(std::string);
	void escrever_para_arquivo(std::string, std::vector<std::string>);
	bool comparar(std::string, std::string);
	std::vector<std::string> trocar(std::vector<std::string>, int, int);
	std::vector<std::string> desmontar(std::vector<std::string>);
public:
	std::vector<std::string> heapsort(std::vector<std::string>);
	OrdenadorIndices(void) {};
	void ordenar_roubando(std::string);
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

	outlet.open(path.c_str(), std::fstream::out);
	for (it = in.begin(); it != in.end(); ++it)
		outlet << *it << std::endl;
	outlet.close();
}

bool OrdenadorIndices::comparar(std::string s, std::string t)
{
	std::cout << "comparar: \n " << s << " " << t << "\n" << (s.compare(t) > 0) << std::endl;
	return (s.compare(t) > 0);
}

std::vector<std::string> OrdenadorIndices::trocar(std::vector<std::string> arr, int n, int m)
{
	std::string temp = arr[n];
	arr[n] = arr[m];
	arr[m] = temp;
	return arr;
}

std::vector<std::string> OrdenadorIndices::desmontar(std::vector<std::string> inlet)
{
	std::vector<std::string> outlet;
	std::string junk;
	int k, n;

	while (inlet.size() > 2)
	{
		junk = inlet.at(1);
		outlet.push_back(junk);

		inlet[1] = inlet.at(inlet.size()-1); // put the largest value into	 root
		k = 1; // node of heap that contains the largest value

		while (2*k < (int) inlet.size()-1)
		{
			if (!comparar(inlet[2*k], inlet[2*k+1]))
				n = 2*k;
			else
				n = 2*k + 1;

			if (!comparar(inlet[k], inlet[n]))
				trocar(inlet, k, n);

			k = n;
		}

		inlet.erase(inlet.begin()+1);
	}

	outlet.push_back(inlet.at(1));
	return outlet;
}

/* implementação do heapsort como descrita por Folk, pg 170 do pdf */
std::vector<std::string> OrdenadorIndices::heapsort(std::vector<std::string> chaves)
{
	std::vector<std::string> heapArray;
	std::vector<std::string>::iterator it;
	int num, k;

	std::cout << "heapsort" << std::endl;


	heapArray.push_back("---");
	for (it = chaves.begin(); it != chaves.end(); ++it)
	{
		heapArray.push_back(*it);
		k=heapArray.size()-1;

		//std::cout << "k:" << k << std::endl;

		while(k>1)
		{
			num=k/2;
			//std::cout << "entrou em while; num:" << num << std::endl;
			//std::cout << comparar(heapArray[k], heapArray[num]) << std::endl;

			if(!comparar(heapArray[k], heapArray[num]))
			{
				std::string array=heapArray[k];
				heapArray[k]=heapArray[num];
				heapArray[num]=array;
				//std::cout << "trocou\n  " << heapArray[k] << heapArray[num] << std::endl;
			}
			k=num;

		}

	}
	return desmontar(heapArray);
}

/*******************
* FUNCOES PUBLICAS *
*******************/

// enquanto não conseguimos implementar o heapsort,
// vamos ordenar o arquivo usando a função std::sort 
void OrdenadorIndices::ordenar_roubando(std::string endereco)
{
	std::vector<std::string> chaves = preencher_do_arquivo(endereco);
	std::sort(chaves.begin(), chaves.end()); // CHEATING
	escrever_para_arquivo(endereco, chaves);
}

void OrdenadorIndices::ordenar (std::string endereco)
{
	escrever_para_arquivo(endereco, heapsort(preencher_do_arquivo(endereco)));
	std::cout << "entrou em ordenar" << std::endl;
}
