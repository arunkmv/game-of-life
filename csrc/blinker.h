#ifndef GAME_OF_LIFE_TEST_BLINKER_H
#define GAME_OF_LIFE_TEST_BLINKER_H

#include "map-io.h"

static void initialize_dut(dut &m) {
}

static void initialize_state(dut &m) {
    std::array<std::array<unsigned char, 3>, 3> blinker_pattern = {{
            {0, 0, 0},
            {1, 1, 1},
            {0, 0, 0}
    }};

    poke<3, 3>(map_3x3_seed(m), blinker_pattern, m);
}

static void display_state(dut &m, int gen) {
    printf("Game Of Life - Blinker Pattern - 3 * 3");
    printf("\n======\n\n");

    peek<3, 3>(map_3x3_curr(m));

    printf("\n======\n\n");
    printf("Generation: %d\n", gen);
}

#endif //GAME_OF_LIFE_TEST_BLINKER_H
