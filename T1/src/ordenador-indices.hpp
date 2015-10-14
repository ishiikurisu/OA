#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "criador-indices.hpp"

class OrdenadorIndices{
	std::string gerar_saida_primaria (std::string);
	std::string ordenar_primario (std::string);
	std::string gerar_saida_secundaria (std::string);
	std::string ordenar_secundario (std:string);
public:
	OrdenadorIndices (void){};
	std::string ordenar_indices (std::string);
};


std::string OrdenadorIndices::gerar_saida_primaria (std::string)
{
	
}
