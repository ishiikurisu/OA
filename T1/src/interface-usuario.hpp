#include <iostream>
#include <criador-indices-primario.hpp>
#include <criador-indices-secundario.hpp>
#include <ordenador-indices.hpp>
#ifdef _WIN32
// #define clear() system("cls")
#define clear() NULL
#else
#define clear() system("clear")
#endif

class InterfaceUsuario
{
public:
	InterfaceUsuario();
	std::string pedir_listas(void);
	bool escolher_opcao(void);
	void setup();
};

InterfaceUsuario::InterfaceUsuario()
{
	return;
}

std::string InterfaceUsuario::pedir_listas()
{
	std::string nome;

	std::cout << "Escreva o nome do arquivo: ";
	std::getline(std::cin, nome);

	return nome;
}

bool InterfaceUsuario::escolher_opcao()
{
	bool permanecer = true;
	int op = -1;
	std::string junk;

	clear();
	std::cout << "Escolha uma opcao:" << std::endl;
	std::cout << "  0. SAIR" << std::endl;
	std::cout << "  1. INCLUIR" << std::endl;
	std::cout << "  2. EXCLUIR" << std::endl;
	std::cout << "  3. ATUALIZAR" << std::endl;
	std::cout << "  4. INTERCALAR" << std::endl;
	std::cout << "Opcao: ";
	std::cin >> op;

	switch (op)
	{
		case 0:
			permanecer = false;
			clear();
			std::cout << "See ya :)" << std::endl;
		break;

		default:
			std::cout << "OPCAO NAO IMPLEMENTADA" << std::endl;
			std::cout << "Aperte `Enter` para sair" << std::endl;
			std::getline(std::cin, junk);
	}

	return permanecer;
}

void InterfaceUsuario::setup()
{
	CriadorIndicesPrimario cip;
	CriadorIndicesSecundario cis;
	OrdenadorIndices oi;
	std::string nome_lista;

	for (int i = 0; i < 2; ++i)
	{
		nome_lista = pedir_listas();
		oi.ordenar(cip.gerar_indices(nome_lista));
		cis.gerar_indices(nome_lista);
	}
}
