#ifndef INTERCALAR_INDICES_HPP
#define INTERCALAR_INDICES_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <criador-indices-primario.hpp>

class IntercaladorIndices
{
	void preparar(std::string);
public:
	IntercaladorIndices() {};
	void intercalar(std::string, std::string);
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

void IntercaladorIndices::preparar(std::string endereco)
{

}

/*******************
* FUNÇÕES PÚBLICAS *
*******************/

void IntercaladorIndices::intercalar(std::string arquivo1, std::string arquivo2)
{
	std::string s1;
	std::string s2;
	std::fstream fs;
	fs.open("lista12.txt");

	preparar();

	fs.close();
}

#endif /* end of include guard: INTERCALAR_INDICES_HPP */
