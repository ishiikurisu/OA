#ifndef BUFFER_H
#define BUFFER_H 0

typedef struct
{
    char *source;
    char *mode;
    char *data;
    int size;
    bool available;
    FILE *stream;
}
BUFFER;

BUFFER* buffer_new(char *source, char *mode, int buffer_size);
void buffer_status(BUFFER *buffer);
BUFFER* buffer_flush(BUFFER *buffer);
BUFFER* buffer_feed(BUFFER *buffer);
void buffer_write(BUFFER *buffer, char *to_write);
char buffer_read(BUFFER *buffer);
int buffer_is_available(BUFFER *buffer);
int buffer_feof(BUFFER *buffer);
char* buffer_read_line(BUFFER *buffer);
void buffer_close(BUFFER *buffer);

#endif
