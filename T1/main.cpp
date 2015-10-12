#include <iostream>
#include "criador-indices-primario.hpp"

std::string pedir_listas()
{
	std::string nome;

	std::cout << "Escreva o nome do arquivo: ";
	std::getline(std::cin, nome);

	return nome;
}

void setup()
{
	CriadorIndicesPrimario cip;
	CriadorIndicesSecundario cis;
	std::string nome_lista;
	// OrdenadorIndices oi;

	nome_lista = pedir_listas();
	cip.gerar_indices(nome_lista);
	cis.gerar_indices(nome_lista);

	nome_lista = pedir_listas();
	cip.gerar_indices(nome_lista);
	cis.gerar_indices(nome_lista);
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
