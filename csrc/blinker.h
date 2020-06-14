#ifndef GAME_OF_LIFE_TEST_BLINKER_H
#define GAME_OF_LIFE_TEST_BLINKER_H

#include "dut.h"

static void initialize_dut(dut &m) {
}

static void initialize_state(dut &m) {
    int blinker_pattern[3][3] =
            {{0, 0, 0},
             {1, 1, 1},
             {0, 0, 0}};

    m.clock = 0;
    m.eval();

    m.io_valid = 1;

    m.io_seedState_0_0 = blinker_pattern[0][0];
    m.io_seedState_0_1 = blinker_pattern[0][1];
    m.io_seedState_0_2 = blinker_pattern[0][2];
    m.io_seedState_1_0 = blinker_pattern[1][0];
    m.io_seedState_1_1 = blinker_pattern[1][1];
    m.io_seedState_1_2 = blinker_pattern[1][2];
    m.io_seedState_2_0 = blinker_pattern[2][0];
    m.io_seedState_2_1 = blinker_pattern[2][1];
    m.io_seedState_2_2 = blinker_pattern[2][2];

    m.clock = 1;
    m.eval();

    m.io_valid = 0;
    m.eval();
}

static void display_state(dut &m, int gen) {
    int currState[3][3] = {
            {m.io_state_0_0, m.io_state_0_1, m.io_state_0_2},
            {m.io_state_1_0, m.io_state_1_1, m.io_state_1_2},
            {m.io_state_2_0, m.io_state_2_1, m.io_state_2_2}
    };

    printf("Game Of Life - Blinker Pattern - 3 * 3");
    printf("\n========\n");
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            if (currState[i][j] == 1)
                printf("* ");
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nGeneration: %d\n", gen);
    printf("\n========\n");
}

#endif //GAME_OF_LIFE_TEST_BLINKER_H
