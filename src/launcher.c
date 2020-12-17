//
// File (launcher.c) created by VT-Ambu (https://github.com/VT-Ambu).
// Date 12/2/20
//

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "launcher.h"
#include "game.h"

extern int errno;

void init(char *path, game_t *game)
{
    char **content = read_files(path);
    if (content == NULL)
        return;
    indexer(content, game);
    add_chars(game);
    free(content);
}

char **read_files(const char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
        return (NULL);
    return (read_lines(fp));
}

char **read_lines(FILE *fp)
{
    int iteration = 0;
    char **res;
    res = calloc(1, sizeof(char *));
    if (res == NULL)
        return (NULL);

    char *buff;
    size_t n = 0;
    int read;
    while (1)
    {
        buff = NULL;
        n = 0;
        if ((read = getline(&buff, &n, fp)) == -1)
        {
            fclose(fp);
            return (res);
        }
        res = realloc(res, (iteration + 1) * sizeof(char *));
        if (res == NULL)
        {
            fclose(fp);
            return (NULL);
        }
        if (buff[read - 1] == '\n')
        {
            buff[read - 1] = '\0';
        }
        res[iteration] = strdup(buff);
        iteration++;
        free(buff);
    }
}

void indexer(char **words, game_t *game)
{
    srand(time(NULL)); // NOLINT(cert-msc51-cpp)
    int index = (rand() % 49) + 1; // NOLINT(cert-msc50-cpp)
    write(game, strlen(words[index]),  words[index]);
}

void add_chars(game_t *game)
{
    int index = 0;
    for (int i = 97; i <= 122; ++i) {
        game->rest[index] = (char) i;
        index++;
    }
    game->length_rest = index;
}