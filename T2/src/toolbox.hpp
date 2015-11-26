#pragma once
#include <stdio.h>

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

} /* toolbox */
