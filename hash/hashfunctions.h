int stupid(char* input)
{
    int output = 0;
    int limit = strlen(input);
    int i;

    for (i = 0; i < limit; ++i)
        output += input[i] * (i + 1);

    return output;
}

int dumb(char* input)
{
    int output = 0;
    int limit = strlen(input);
    int i;

    for (i = 0; i < limit; ++i)
        output += input[i];

    return (output << 2) + (output >> 2);
}
