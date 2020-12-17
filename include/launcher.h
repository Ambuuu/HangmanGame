//
// File (launcher.h) created by VT-Ambu (https://github.com/VT-Ambu).
// Date 12/2/20
//

#ifndef HANGMANGAME_LAUNCHER_H
#define HANGMANGAME_LAUNCHER_H

#include <stdio.h>
#include "game.h"

void init(char *path, game_t *game);

char **read_lines(FILE *fp);
char **read_files(const char *filepath);
void indexer(char **worlds, game_t *game);
void add_chars(game_t *game);

#endif //HANGMANGAME_LAUNCHER_H
