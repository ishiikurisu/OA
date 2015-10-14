#include <interface-usuario.hpp>

int main(int argc, char const *argv[]) {
	InterfaceUsuario in;
	for (in.setup(); in.escolher_opcao(); NULL);
	return 0;
}
