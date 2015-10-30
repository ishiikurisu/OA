#ifndef MOSTRAR_INDICES_HPP
#define MOSTRAR_INDICES_HPP
#include <fstream>

class MostradorIndices
{
public:
	MostradorIndices() {};
	void mostrar(std::string path)
	{
		std::fstream fs;
		fs.open(path.c_str(), std::fstream::in);
		std::string line;
		for (std::getline(fs, line);
	         line.length() > 0;
		     std::cout << line << std::endl, std::getline(fs, line));

		fs.close();
	}
};

#endif /* end of include guard: MOSTRAR_INDICES_HPP */
