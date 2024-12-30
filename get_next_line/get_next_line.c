#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_read = 0, buffer_pos = 0;
    char *line;
    int i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
	
    line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!line)
        return (NULL);

    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }

        line[i++] = buffer[buffer_pos++];

        if (line[i - 1] == '\n')
            break;
    }
    if (i == 0)
    {
        free(line);
        return (NULL);
    }
    line[i] = '\0';
    return (line);
}
