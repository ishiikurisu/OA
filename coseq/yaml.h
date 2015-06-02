#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "list.h"
#include "coseq.h"

LIST* yaml_to_list(char* yaml_name)
{
	FILE* yaml = fopen(yaml_name, "r");
	LIST* list = new_list();
	char* data = read_from_file(yaml);
	
	data = read_from_file(yaml);
	while (data = read_from_file(yaml), compare(data,"...") != EQUAL)
	{
		data = substring(data, 2, strlen(data));
		list = add_to_list(list, data);
	}

	fclose(yaml);
	return list;
}

void yamlpipe_to_pipe()
{
	char* line;

	line = read_from_file(stdin);
	line = read_from_file(stdin);
	while(line = read_from_file(stdin), compare(line, "...") != EQUAL)
		printf("%s\n", substring(line, 2, strlen(line)));
}

void pipe_to_yaml(char* title)
{
	char* line;

	if (title == NULL)
		title = "YAML";
	printf("---\n%s:\n", title);

	while (line = read_from_file(stdin))
		printf("- %s\n", line);

	printf("...\n");
}


