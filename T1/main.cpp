#include <iostream>
#include "criador-indices.hpp"

std::string pedir_listas()
{
	std::string nome;

	std::cout << "Escreva o nome do arquivo: ";
	std::getline(std::cin, nome);

	return nome;
}

void setup()
{
	CriadorIndices ci;
	// OrdenadorIndices oi;

	ci.gerar_indices(pedir_listas());
	ci.gerar_indices(pedir_listas());
	// oi.ordenar_indices(ci.gerar_indices(pedir_listas()));
	// oi.ordenar_indices(ci.gerar_indices(pedir_listas()));
}

int main(int argc, char const *argv[]) {
	setup();
	/*
	while (true)
		loop();
	*/
	return 0;
}
