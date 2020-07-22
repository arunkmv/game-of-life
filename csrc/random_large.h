#ifndef GAME_OF_LIFE_RANDOM_H
#define GAME_OF_LIFE_RANDOM_H

#include "helpers.h"
#include <stdlib.h>
#include <ctime>

static void initialize_dut(dut &m) {
}

static void initialize_state(dut &m) {
    srand((unsigned) time(0));
    std::array<std::array<unsigned char, 40>, 40> random_pattern;

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            random_pattern[i][j] = (rand() % 2);
        }
    }

    poke<40, 40>(random_pattern, m);
}

static void display_state(dut &m, int gen) {
    printf("Game Of Life - Random Pattern - 40 * 40");
    printf("\n======\n\n");

    peek<40, 40>(m);

    printf("\n======\n\n");
    printf("Generation: %d\n", gen);
}

#endif //GAME_OF_LIFE_RANDOM_H
