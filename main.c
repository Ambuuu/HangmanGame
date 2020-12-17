#include <malloc.h>
#include "launcher.h"

int main() {
    game_t *game = NULL;
    game = calloc(1, sizeof(game_t));
    return launch(game);
}