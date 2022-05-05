#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char    *str_join(char *base, const char *str, size_t n)
{
    size_t  len;

    len = n + 1;
    if (base)
        len += strlen(base);
    base = realloc(base, len);
    if (!base)
        return (NULL);
    strlcat(base, str, len);
    return (base);
}

char *resolve_vars(const char *str)
{
    char    *final;
    char var[255];
    char    *val;
    int i;
    int j;

    final = strdup("");
    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            j = 0;
            ++i;
            while (str[i])
            {
                if (str[i] >= 'A' && str[i] <= 'Z')
                {
                    var[j++] = str[i];
                }
                else
                    break ;
                ++i;
            }
            var[j] = 0;
            val = getenv(var);
            if (val)
                final = str_join(final, val, strlen(val));
        }
        else
        {
            j = i;
            while (str[i] && str[i] != '$')
                ++i;
            final = str_join(final, str + j, i - j);
        }
    }
    return (final);
}


void parse_line(const char *line, int len)
{
    int i;
    int tokstart;
    int str;

    i = 0;
    str = 0;
    while (i < len)
    {
        while (i < len && line[i] == ' ')
            ++i;

        if (line[i] == '"')
        {
            str = 1;
            ++i;
        }
        tokstart = i;
        while (i < len)
        {
            if (str && line[i] == '"')
            {
                break;
            }
            else if (!str && (line[i] == ' ' || line[i] == '\n'))
                break ;
            ++i;
        }
        if (i == tokstart)
            break ;

        if (str)
        {
            char *s = strndup(line + tokstart, i - tokstart);
            char *resolved = resolve_vars(s);

            free(s);
            printf("token: %s\n", resolved);
            free(resolved);
        }
        else
            printf("Token %.*s\n", i - tokstart, line + tokstart);

        if (str && line[i] == '"')
        {
            ++i;
            str = 0;
        }
    }
    printf("\n");
}

int main(void) {
    char line[128];
    int n;

    printf("%s\n", resolve_vars("Hello $WORLD I am in $HOME__"));

    while (1) {
        printf("NASA_Server_01> ");
        fflush(stdout);
        n = read(STDIN_FILENO, line, sizeof(line));

        if (n == 0)
            break ;
        if (n < 0)
        {
            perror("read");
            return 1;
        }

        parse_line(line, n);
    }
    return 0;
}