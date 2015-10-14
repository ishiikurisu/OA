#include <criador-indices-primario.hpp>
#include <criador-indices-secundario.hpp>
#include <interface-usuario.hpp>

bool APP_ON = true;
InterfaceUsuario interface;

void setup()
{
	CriadorIndicesPrimario cip;
	CriadorIndicesSecundario cis;
	std::string nome_lista;
	// OrdenadorIndices oi;

	nome_lista = interface.pedir_listas();
	cip.gerar_indices(nome_lista);
	cis.gerar_indices(nome_lista);

	nome_lista = interface.pedir_listas();
	cip.gerar_indices(nome_lista);
	cis.gerar_indices(nome_lista);
	// oi.ordenar_indices(ci.gerar_indices(pedir_listas()));
	// oi.ordenar_indices(ci.gerar_indices(pedir_listas()));
}

void loop()
{
	APP_ON = interface.escolher_opcao();
}

int main(int argc, char const *argv[]) {
	setup();
	while (APP_ON)
		loop();

	return 0;
}
