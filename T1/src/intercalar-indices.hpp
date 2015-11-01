#ifndef INTERCALAR_INDICES_HPP
#define INTERCALAR_INDICES_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <criador-indices-primario.hpp>
#define SAIDA ("lista12.txt")

class IntercaladorIndices
{
	int comparar(std::string, std::string);
	std::fstream in1;
	std::fstream in2;
public:
	IntercaladorIndices() {};
	void intercalar(std::string, std::string);
};

/*******************
* FUNÇÕES PRIVADAS *
*******************/

#define MENOR (-1)
#define MAIOR (1)
#define IGUAL (0)
int IntercaladorIndices::comparar(std::string s, std::string t)
{
	int comp = 0;
	int resultado = IGUAL;

	if (s.length() <= 1)
		resultado = MAIOR;
	else if (t.length() <= 1)
		resultado = MENOR;
	else {
		comp = s.compare(t);
		if (comp > 0)
			resultado = MAIOR;
		else if (comp < 0)
			resultado = MENOR;
	}

	return resultado;
}


/*******************
* FUNÇÕES PÚBLICAS *
*******************/

void IntercaladorIndices::intercalar(std::string arquivo1, std::string arquivo2)
{
	std::string s1;
	std::string s2;
	std::fstream out;

	out.open(SAIDA, std::fstream::out);
	in1.open(arquivo1.c_str());
	in2.open(arquivo2.c_str());
	std::getline(in1, s1);
	std::getline(in2, s2);

	while (s1.length() > 1 && s2.length() > 1) {
		switch (comparar(s1, s2)) {
			case MAIOR:
				out << s2 << std::endl;
				std::getline(in2, s2);
			break;

			case MENOR:
				out << s1 << std::endl;
				std::getline(in1, s1);
			break;

			default:
				out << s1 << std::endl;
				std::getline(in1, s1);
				std::getline(in2, s2);
		}
	}

	in1.close();
	in2.close();
	out.close();
}

#undef MENOR
#undef MAIOR
#undef IGUAL
#undef SAIDA
#endif /* end of include guard: INTERCALAR_INDICES_HPP */
