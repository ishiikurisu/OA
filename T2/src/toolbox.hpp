#pragma once
#include <stdio.h>
#include <sys/stat.h>
#include <vector>

namespace toolbox {

	int str2num(const char *str)
	{
		int u = 0;
		sscanf(str, "%d", &u);
		return u;
	}

	void cat(const char *msg)
	{
		printf("%s\n", msg);
	}

	void debug(const char *msg)
	{
		printf("!DEBUG! %s\n", msg);
	}

	bool file_exists(const char *filename)
	{
		struct stat buf;

		if (stat(filename, &buf) != -1)
			return true;
		else
			return false;
	}

	unsigned int encontrar(std::vector<unsigned int> arr, unsigned int ui)
	{
		for (unsigned int i = 0; i < arr.size(); ++i)
			if (arr[i] == ui)
				return i;
		return -1;
	}

} /* toolbox */
