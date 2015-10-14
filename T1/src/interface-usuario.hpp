#include <iostream>
#ifdef _WIN32
#define clear() system("cls")
#else
#define clear() system("clear")
#endif

class InterfaceUsuario
{
public:
	InterfaceUsuario();
	std::string pedir_listas(void);
	bool escolher_opcao(void);
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
