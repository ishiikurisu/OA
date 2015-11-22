#pragma once
#include <stdio.h>

namespace toolbox {

	int str2num(const char* str)
	{
		int u = 0;
		sscanf(str, "%d", &u);
		return u;
	}

} /* toolbox */
