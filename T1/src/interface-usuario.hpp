#include <iostream>
#include <vector>
#include <mostrar-indices.hpp>
#include <criador-indices-primario.hpp>
#include <criador-indices-secundario.hpp>
#include <ordenador-indices.hpp>
#include <adicionar-indices.hpp>
#include <excluir-indices.hpp>
#include <atualizar-indices.hpp>
#include <intercalar-indices.hpp>
#include <toolbox.hpp>
#ifdef _WIN32
#define clear() system("cls")
#else
#define clear() system("clear")
#endif

class InterfaceUsuario
{
	std::vector<std::string> listas;
	MostradorIndices mostrador;
public:
	InterfaceUsuario();
	std::string pedir_listas(void);
	bool escolher_opcao(void);
	void setup();
	void adicionar();
	void excluir();
	void atualizar();
	void intercalar();
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

void InterfaceUsuario::setup()
{
	CriadorIndicesPrimario cip;
	CriadorIndicesSecundario cis;
	OrdenadorIndices oi;
	std::string nome_lista;

	for (int i = 0; i < 2; ++i)
	{
		nome_lista = pedir_listas();
		listas.push_back(nome_lista);
		nome_lista = cip.gerar_indices(nome_lista);
		oi.ordenar_roubando(nome_lista);
		cis.gerar_indices(nome_lista);
	}
}

bool InterfaceUsuario::escolher_opcao()
{
	bool permanecer = true;
	int op = -1;
	std::string junk;

	// clear();
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
			std::cout << "See ya :)" << std::endl;
		break;

		case 1:
			adicionar();
		break;

		case 2:
			excluir();
		break;

		case 3:
			atualizar();
		break;

		case 4:
			intercalar();
		break;

		default:
			std::cout << "OPCAO NAO IMPLEMENTADA" << std::endl;
			std::cout << "Aperte `Enter` para sair" << std::endl;
			std::getline(std::cin, junk);
			std::getline(std::cin, junk);
	}

	return permanecer;
}

void InterfaceUsuario::adicionar()
{
	const char* campos[] = {"Matricula", "Nome", "OP", "Curso", "Turma", NULL};
	AdicionadorIndices ai;
	std::vector<std::string>::iterator l;
	std::vector<std::string> dados;
	std::string dado;
	std::string arquivo;
	int i;

	std::cout << "Adicionar em qual arquivo?" << std::endl;
	for (i = 1, l = listas.begin(); l != listas.end(); ++l, ++i)
		std::cout << "  " << i << ". " << *l << std::endl;
	std::getline(std::cin, dado);
	std::getline(std::cin, dado);
	i = stoi(dado.c_str());
	arquivo = listas.at(--i);
	for (i = 0; campos[i] != NULL; ++i)
	{
		std::cout << campos[i] << ": " << std::endl;
		std::getline(std::cin, dado);
		dados.push_back(dado);
	}

	std::cout << "--- # Antes:" << std::endl; mostrador.mostrar(arquivo);
	ai.adicionar(arquivo, dados);
	std::cout << "--- # Depois:" << std::endl; mostrador.mostrar(arquivo);
	std::cout << "..." << std::endl;
}

void InterfaceUsuario::excluir()
{
	ApagadorIndices ai;
	std::string matricula;
	std::vector<std::string>::iterator lista;

	std::cout << "Digite a matricula: " << std::endl;
	std::getline(std::cin, matricula);
	std::getline(std::cin, matricula);

	for (lista = listas.begin(); lista != listas.end(); ++lista)
	{
		std::cout << "--- # Antes: " << std::endl;
		mostrador.mostrar(*lista);
		ai.excluir(*lista, matricula);
		std::cout << "--- # Depois: " << std::endl;
		mostrador.mostrar(*lista);
	}
	/* excluir */
}

void InterfaceUsuario::atualizar()
{
	AtualizadorIndices ai;
	std::string matricula_antiga;
	std::string matricula_nova;
	std::string nome;

	std::cout << "Digite sua matricula" << std::endl;
	std::getline(std::cin, matricula_antiga);
	/* mostrar nome da pessoa */
	std::cout << "Digite sua nova matricula";
	std::cout << " (deixe em branco para a mesma matricula): " << std::endl;
	std::getline(std::cin, matricula_nova);
	std::cout << "Digite seu nome";
	std::cout << " (deixe em branco para o mesmo nome): " << std::endl;
	std::getline(std::cin, nome);

	ai.atualizar();
}

void InterfaceUsuario::intercalar()
{
	IntercaladorIndices ii;

	ii.intercalar(listas[0], listas[1]);
	std::cout << "--- # lista intercalada" << std::endl;
	mostrador.mostrar("lista12.txt");
	std::cout << "..." << std::endl;
}
