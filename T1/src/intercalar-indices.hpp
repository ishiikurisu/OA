#ifndef INTERCALAR_INDICES_HPP
#define INTERCALAR_INDICES_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class IntercaladorIndices
{
public:
	IntercaladorIndices() {};
	void intercalar(std::string, std::string);
};

void IntercaladorIndices::intercalar(std::string arquivo1, std::string arquivo2)
{
	std::fstream fs;
	fs.open("lista12.txt");

	

	fs.close();
}

#endif /* end of include guard: INTERCALAR_INDICES_HPP */
