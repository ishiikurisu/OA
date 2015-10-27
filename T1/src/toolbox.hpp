#pragma once
#include <stdio.h>

int stoi(const char *str)
{
	int n;
	sscanf(str, "%d", &n);
	return n;
}
