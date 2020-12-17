//
// File (game.h) created by VT-Ambu (https://github.com/VT-Ambu)
// Date 12/4/20
//

#ifndef HANGMANGAME_GAME_H
#define HANGMANGAME_GAME_H

#include <stdio.h>

typedef struct {
    int found;
    int try;
    char *word;
    char *word_s;
    char *rest;
    int length_rest;
    int length;
} game_t;

int launch(game_t *game);
int write(game_t *game, size_t length, const char* word);
void close(game_t *game);
void stop(game_t *game);

int start(game_t *game);
char ask();
int verify(char c, game_t *game);
int replace(char c, game_t *game);
int already_used(game_t *game, char c);

void remove_letters(game_t *game, char c);
void print_letters(game_t *game);
#endif //HANGMANGAME_GAME_H
