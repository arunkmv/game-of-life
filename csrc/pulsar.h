#ifndef GAME_OF_LIFE_PULSAR_H
#define GAME_OF_LIFE_PULSAR_H

#include "map-io.h"

static void initialize_dut(dut &m) {
}

static void initialize_state(dut &m) {
    std::array<std::array<unsigned char, 15>, 15> pulsar_pattern = {{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    }};

    poke<15, 15>(map_15x15_seed(m), pulsar_pattern, m);
}

static void display_state(dut &m, int gen) {
    printf("Game Of Life - Pulsar Pattern - 15 * 15");
    printf("\n==============================\n\n");

    peek<15, 15>(map_15x15_curr(m));

    printf("\n==============================\n\n");
    printf("Generation: %d\n", gen);
}

#endif //GAME_OF_LIFE_PULSAR_H
