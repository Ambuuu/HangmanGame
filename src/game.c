//
// File (game.c) created by VT-Ambu (https://github.com/VT-Ambu)
// Date 12/4/20
//

#include <malloc.h>
#include <string.h>
#include "game.h"
#include "launcher.h"

int launch(game_t *game)
{
    game->found = 0;
    game->length = 0;
    game->word = calloc(game->length + 1, sizeof(char));
    game->word_s = calloc(game->length + 1, sizeof(char));
    game->rest = calloc(26, sizeof(char));
    if (game->word == NULL)
        return 1;
    game->word[0] = '\0';
    init("../worlds_list.txt", game);
    return start(game);
}

int write(game_t *game, size_t length, const char* word)
{
    game->word = realloc(game->word, length + 1);
    game->word_s = realloc(game->word_s, length + 1);
    if (game->word == NULL)
        return 1;

    for (size_t i = 0; i < length; ++i) {
        game->word[i] = word[i];
        game->word_s[i] = '_';
    }
    game->word[length] = '\0';
    game->word_s[length] = '\0';
    game->length = length;
    return 0;
}

void close(game_t *game)
{
    free(game->word);
    free(game->word_s);
    free(game->rest);
    free(game);
}

int start(game_t *game)
{
    printf("%s\n\n", "Welcome to my HangmanGame write in C ! Good luck!");
    print_letters(game);
    printf("%s : %s\n", "Word", game->word_s);

    while (game->found != 1)
    {
        char c = ask();
        int found = verify(c, game);
        if (found == 0)
            break;
        print_letters(game);
        printf("%s : %s\n", "Word", game->word_s);
        fflush(stdin);
    }

    close(game);
    return 0;
}

void print_letters(game_t *game)
{
    printf("%s : ", "Remaining letters");
    for (int i = 0; i < game->length_rest; ++i) {
        printf("%c  ", game->rest[i]);
    }
    printf("\n");
}

char ask()
{
    char c;
    fflush(stdin);
    printf("%s : ", "Enter a letter");
    scanf("%*[\n]");
    fflush(stdin);
    scanf("%c", &c);
    return c;
}

int verify(char c, game_t *game)
{

    int used = already_used(game, c);
    if (used == 0)
        return 1;
    remove_letters(game, c);
    game->try++;

    if (strchr(game->word, c) != NULL)
    {
        int found = replace(c, game);
        if (found == 0)
            return 0;
        remove_letters(game, c);
    } else {
        printf("%s%c%s\n%s\n\n", "The word hasn't '", c, "'!", "Try again.");
        fflush(stdin);
    }

    return 1;
}

int replace(char c, game_t *game)
{
    for (int i = 0; i < game->length; ++i) {
        if (game->word[i] == c)
        {
            game->word_s[i] = c;
            printf("%s%c%s\n\n", "The word has '", c, "'!");
            fflush(stdin);
        }
    }

    if (strcmp(game->word_s, game->word) == 0)
    {
        stop(game);
        return 0;
    }

    return 1;
}

void remove_letters(game_t *game, char c)
{
    for (int i = 0; i < game->length_rest; ++i) {
        if (game->rest[i] == c)
        {
            game->rest[i] = 0;
        }
    }
}

int already_used(game_t *game, char c)
{
    int found = 0;
    for (int i = 0; i < game->length_rest; ++i) {
        if (game->rest[i] == c)
        {
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("%s\n%s\n\n", "You have already used this letter!", "Try another !");
    }

    return found;
}

void stop(game_t *game)
{
    game->found = 1;
    printf("%s\n", "Good game !");
    printf("%s : %d %s : %s\n", "You have found the word with", game->try, "try!\nIt was", game->word);
}