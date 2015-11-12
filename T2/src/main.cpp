#include <interface-usuario.hpp>

int main(int argc, char const *argv[]) {
	InterfaceUsuario ui;
	for (ui.setup(); ui.draw(););
	return 0;
}
