#ifndef GAME_OF_LIFE_MAP_IO_H
#define GAME_OF_LIFE_MAP_IO_H

#include "dut.h"
#include <array>

template<size_t gridX, size_t gridY>
static void poke(std::array<std::array<unsigned char*, gridX>, gridY> seedState,
                 std::array<std::array<unsigned char, gridX>, gridY> pattern,
                 dut &m) {
    m.clock = 0;
    m.eval();
    m.io_valid = 1;

    for (int i = 0; i < gridY; i++) {
        for (int j = 0; j < gridX; j++) {
            *seedState[i][j] = pattern[i][j];
        }
    }

    m.clock = 1;
    m.eval();
    m.io_valid = 0;
    m.eval();
}

template<size_t gridX, size_t gridY>
static void peek(std::array<std::array<unsigned char*, gridX>, gridY> currState) {
    for (int i = gridY - 1; i >= 0; i--) {
        for (int j = gridX - 1; j >= 0; j--) {
            if (*currState[i][j] == 1)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

static std::array<std::array<unsigned char*, 3>, 3> map_3x3_seed(dut &m) {
    return std::array<std::array<unsigned char*, 3>, 3>({{
        {&m.io_seedState_0_0, &m.io_seedState_0_1, &m.io_seedState_0_2},
        {&m.io_seedState_1_0, &m.io_seedState_1_1, &m.io_seedState_1_2},
        {&m.io_seedState_2_0, &m.io_seedState_2_1, &m.io_seedState_2_2}
    }});
}

static std::array<std::array<unsigned char*, 3>, 3> map_3x3_curr(dut &m) {
    return std::array<std::array<unsigned char*, 3>, 3>({{
        {&m.io_state_0_0, &m.io_state_0_1, &m.io_state_0_2},
        {&m.io_state_1_0, &m.io_state_1_1, &m.io_state_1_2},
        {&m.io_state_2_0, &m.io_state_2_1, &m.io_state_2_2}
    }});
}

#endif //GAME_OF_LIFE_MAP_IO_H
