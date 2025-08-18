#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    nread = getline(&line, &len, stdin);

    if (nread == -1)
    {
        perror("Abort");
        return (-1);
    }
    printf("%s", line);
free(line);
return (0);
}