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

static std::array<std::array<unsigned char*, 15>, 15> map_15x15_seed(dut &m) {
    return std::array<std::array<unsigned char*, 15>, 15>({{
            { &m.io_seedState_0_0,  &m.io_seedState_0_1,  &m.io_seedState_0_2,  &m.io_seedState_0_3,  &m.io_seedState_0_4,  &m.io_seedState_0_5,  &m.io_seedState_0_6,  &m.io_seedState_0_7,  &m.io_seedState_0_8,  &m.io_seedState_0_9,  &m.io_seedState_0_10,  &m.io_seedState_0_11,  &m.io_seedState_0_12,  &m.io_seedState_0_13,  &m.io_seedState_0_14},
            { &m.io_seedState_1_0,  &m.io_seedState_1_1,  &m.io_seedState_1_2,  &m.io_seedState_1_3,  &m.io_seedState_1_4,  &m.io_seedState_1_5,  &m.io_seedState_1_6,  &m.io_seedState_1_7,  &m.io_seedState_1_8,  &m.io_seedState_1_9,  &m.io_seedState_1_10,  &m.io_seedState_1_11,  &m.io_seedState_1_12,  &m.io_seedState_1_13,  &m.io_seedState_1_14},
            { &m.io_seedState_2_0,  &m.io_seedState_2_1,  &m.io_seedState_2_2,  &m.io_seedState_2_3,  &m.io_seedState_2_4,  &m.io_seedState_2_5,  &m.io_seedState_2_6,  &m.io_seedState_2_7,  &m.io_seedState_2_8,  &m.io_seedState_2_9,  &m.io_seedState_2_10,  &m.io_seedState_2_11,  &m.io_seedState_2_12,  &m.io_seedState_2_13,  &m.io_seedState_2_14},
            { &m.io_seedState_3_0,  &m.io_seedState_3_1,  &m.io_seedState_3_2,  &m.io_seedState_3_3,  &m.io_seedState_3_4,  &m.io_seedState_3_5,  &m.io_seedState_3_6,  &m.io_seedState_3_7,  &m.io_seedState_3_8,  &m.io_seedState_3_9,  &m.io_seedState_3_10,  &m.io_seedState_3_11,  &m.io_seedState_3_12,  &m.io_seedState_3_13,  &m.io_seedState_3_14},
            { &m.io_seedState_4_0,  &m.io_seedState_4_1,  &m.io_seedState_4_2,  &m.io_seedState_4_3,  &m.io_seedState_4_4,  &m.io_seedState_4_5,  &m.io_seedState_4_6,  &m.io_seedState_4_7,  &m.io_seedState_4_8,  &m.io_seedState_4_9,  &m.io_seedState_4_10,  &m.io_seedState_4_11,  &m.io_seedState_4_12,  &m.io_seedState_4_13,  &m.io_seedState_4_14},
            { &m.io_seedState_5_0,  &m.io_seedState_5_1,  &m.io_seedState_5_2,  &m.io_seedState_5_3,  &m.io_seedState_5_4,  &m.io_seedState_5_5,  &m.io_seedState_5_6,  &m.io_seedState_5_7,  &m.io_seedState_5_8,  &m.io_seedState_5_9,  &m.io_seedState_5_10,  &m.io_seedState_5_11,  &m.io_seedState_5_12,  &m.io_seedState_5_13,  &m.io_seedState_5_14},
            { &m.io_seedState_6_0,  &m.io_seedState_6_1,  &m.io_seedState_6_2,  &m.io_seedState_6_3,  &m.io_seedState_6_4,  &m.io_seedState_6_5,  &m.io_seedState_6_6,  &m.io_seedState_6_7,  &m.io_seedState_6_8,  &m.io_seedState_6_9,  &m.io_seedState_6_10,  &m.io_seedState_6_11,  &m.io_seedState_6_12,  &m.io_seedState_6_13,  &m.io_seedState_6_14},
            { &m.io_seedState_7_0,  &m.io_seedState_7_1,  &m.io_seedState_7_2,  &m.io_seedState_7_3,  &m.io_seedState_7_4,  &m.io_seedState_7_5,  &m.io_seedState_7_6,  &m.io_seedState_7_7,  &m.io_seedState_7_8,  &m.io_seedState_7_9,  &m.io_seedState_7_10,  &m.io_seedState_7_11,  &m.io_seedState_7_12,  &m.io_seedState_7_13,  &m.io_seedState_7_14},
            { &m.io_seedState_8_0,  &m.io_seedState_8_1,  &m.io_seedState_8_2,  &m.io_seedState_8_3,  &m.io_seedState_8_4,  &m.io_seedState_8_5,  &m.io_seedState_8_6,  &m.io_seedState_8_7,  &m.io_seedState_8_8,  &m.io_seedState_8_9,  &m.io_seedState_8_10,  &m.io_seedState_8_11,  &m.io_seedState_8_12,  &m.io_seedState_8_13,  &m.io_seedState_8_14},
            { &m.io_seedState_9_0,  &m.io_seedState_9_1,  &m.io_seedState_9_2,  &m.io_seedState_9_3,  &m.io_seedState_9_4,  &m.io_seedState_9_5,  &m.io_seedState_9_6,  &m.io_seedState_9_7,  &m.io_seedState_9_8,  &m.io_seedState_9_9,  &m.io_seedState_9_10,  &m.io_seedState_9_11,  &m.io_seedState_9_12,  &m.io_seedState_9_13,  &m.io_seedState_9_14},
            {&m.io_seedState_10_0, &m.io_seedState_10_1, &m.io_seedState_10_2, &m.io_seedState_10_3, &m.io_seedState_10_4, &m.io_seedState_10_5, &m.io_seedState_10_6, &m.io_seedState_10_7, &m.io_seedState_10_8, &m.io_seedState_10_9, &m.io_seedState_10_10, &m.io_seedState_10_11, &m.io_seedState_10_12, &m.io_seedState_10_13, &m.io_seedState_10_14},
            {&m.io_seedState_11_0, &m.io_seedState_11_1, &m.io_seedState_11_2, &m.io_seedState_11_3, &m.io_seedState_11_4, &m.io_seedState_11_5, &m.io_seedState_11_6, &m.io_seedState_11_7, &m.io_seedState_11_8, &m.io_seedState_11_9, &m.io_seedState_11_10, &m.io_seedState_11_11, &m.io_seedState_11_12, &m.io_seedState_11_13, &m.io_seedState_11_14},
            {&m.io_seedState_12_0, &m.io_seedState_12_1, &m.io_seedState_12_2, &m.io_seedState_12_3, &m.io_seedState_12_4, &m.io_seedState_12_5, &m.io_seedState_12_6, &m.io_seedState_12_7, &m.io_seedState_12_8, &m.io_seedState_12_9, &m.io_seedState_12_10, &m.io_seedState_12_11, &m.io_seedState_12_12, &m.io_seedState_12_13, &m.io_seedState_12_14},
            {&m.io_seedState_13_0, &m.io_seedState_13_1, &m.io_seedState_13_2, &m.io_seedState_13_3, &m.io_seedState_13_4, &m.io_seedState_13_5, &m.io_seedState_13_6, &m.io_seedState_13_7, &m.io_seedState_13_8, &m.io_seedState_13_9, &m.io_seedState_13_10, &m.io_seedState_13_11, &m.io_seedState_13_12, &m.io_seedState_13_13, &m.io_seedState_13_14},
            {&m.io_seedState_14_0, &m.io_seedState_14_1, &m.io_seedState_14_2, &m.io_seedState_14_3, &m.io_seedState_14_4, &m.io_seedState_14_5, &m.io_seedState_14_6, &m.io_seedState_14_7, &m.io_seedState_14_8, &m.io_seedState_14_9, &m.io_seedState_14_10, &m.io_seedState_14_11, &m.io_seedState_14_12, &m.io_seedState_14_13, &m.io_seedState_14_14}
        }});
}

static std::array<std::array<unsigned char*, 15>, 15> map_15x15_curr(dut &m) {
    return std::array<std::array<unsigned char*, 15>, 15>({{
            { &m.io_state_0_0,  &m.io_state_0_1,  &m.io_state_0_2,  &m.io_state_0_3,  &m.io_state_0_4,  &m.io_state_0_5,  &m.io_state_0_6,  &m.io_state_0_7,  &m.io_state_0_8,  &m.io_state_0_9,  &m.io_state_0_10,  &m.io_state_0_11,  &m.io_state_0_12,  &m.io_state_0_13,  &m.io_state_0_14},
            { &m.io_state_1_0,  &m.io_state_1_1,  &m.io_state_1_2,  &m.io_state_1_3,  &m.io_state_1_4,  &m.io_state_1_5,  &m.io_state_1_6,  &m.io_state_1_7,  &m.io_state_1_8,  &m.io_state_1_9,  &m.io_state_1_10,  &m.io_state_1_11,  &m.io_state_1_12,  &m.io_state_1_13,  &m.io_state_1_14},
            { &m.io_state_2_0,  &m.io_state_2_1,  &m.io_state_2_2,  &m.io_state_2_3,  &m.io_state_2_4,  &m.io_state_2_5,  &m.io_state_2_6,  &m.io_state_2_7,  &m.io_state_2_8,  &m.io_state_2_9,  &m.io_state_2_10,  &m.io_state_2_11,  &m.io_state_2_12,  &m.io_state_2_13,  &m.io_state_2_14},
            { &m.io_state_3_0,  &m.io_state_3_1,  &m.io_state_3_2,  &m.io_state_3_3,  &m.io_state_3_4,  &m.io_state_3_5,  &m.io_state_3_6,  &m.io_state_3_7,  &m.io_state_3_8,  &m.io_state_3_9,  &m.io_state_3_10,  &m.io_state_3_11,  &m.io_state_3_12,  &m.io_state_3_13,  &m.io_state_3_14},
            { &m.io_state_4_0,  &m.io_state_4_1,  &m.io_state_4_2,  &m.io_state_4_3,  &m.io_state_4_4,  &m.io_state_4_5,  &m.io_state_4_6,  &m.io_state_4_7,  &m.io_state_4_8,  &m.io_state_4_9,  &m.io_state_4_10,  &m.io_state_4_11,  &m.io_state_4_12,  &m.io_state_4_13,  &m.io_state_4_14},
            { &m.io_state_5_0,  &m.io_state_5_1,  &m.io_state_5_2,  &m.io_state_5_3,  &m.io_state_5_4,  &m.io_state_5_5,  &m.io_state_5_6,  &m.io_state_5_7,  &m.io_state_5_8,  &m.io_state_5_9,  &m.io_state_5_10,  &m.io_state_5_11,  &m.io_state_5_12,  &m.io_state_5_13,  &m.io_state_5_14},
            { &m.io_state_6_0,  &m.io_state_6_1,  &m.io_state_6_2,  &m.io_state_6_3,  &m.io_state_6_4,  &m.io_state_6_5,  &m.io_state_6_6,  &m.io_state_6_7,  &m.io_state_6_8,  &m.io_state_6_9,  &m.io_state_6_10,  &m.io_state_6_11,  &m.io_state_6_12,  &m.io_state_6_13,  &m.io_state_6_14},
            { &m.io_state_7_0,  &m.io_state_7_1,  &m.io_state_7_2,  &m.io_state_7_3,  &m.io_state_7_4,  &m.io_state_7_5,  &m.io_state_7_6,  &m.io_state_7_7,  &m.io_state_7_8,  &m.io_state_7_9,  &m.io_state_7_10,  &m.io_state_7_11,  &m.io_state_7_12,  &m.io_state_7_13,  &m.io_state_7_14},
            { &m.io_state_8_0,  &m.io_state_8_1,  &m.io_state_8_2,  &m.io_state_8_3,  &m.io_state_8_4,  &m.io_state_8_5,  &m.io_state_8_6,  &m.io_state_8_7,  &m.io_state_8_8,  &m.io_state_8_9,  &m.io_state_8_10,  &m.io_state_8_11,  &m.io_state_8_12,  &m.io_state_8_13,  &m.io_state_8_14},
            { &m.io_state_9_0,  &m.io_state_9_1,  &m.io_state_9_2,  &m.io_state_9_3,  &m.io_state_9_4,  &m.io_state_9_5,  &m.io_state_9_6,  &m.io_state_9_7,  &m.io_state_9_8,  &m.io_state_9_9,  &m.io_state_9_10,  &m.io_state_9_11,  &m.io_state_9_12,  &m.io_state_9_13,  &m.io_state_9_14},
            {&m.io_state_10_0, &m.io_state_10_1, &m.io_state_10_2, &m.io_state_10_3, &m.io_state_10_4, &m.io_state_10_5, &m.io_state_10_6, &m.io_state_10_7, &m.io_state_10_8, &m.io_state_10_9, &m.io_state_10_10, &m.io_state_10_11, &m.io_state_10_12, &m.io_state_10_13, &m.io_state_10_14},
            {&m.io_state_11_0, &m.io_state_11_1, &m.io_state_11_2, &m.io_state_11_3, &m.io_state_11_4, &m.io_state_11_5, &m.io_state_11_6, &m.io_state_11_7, &m.io_state_11_8, &m.io_state_11_9, &m.io_state_11_10, &m.io_state_11_11, &m.io_state_11_12, &m.io_state_11_13, &m.io_state_11_14},
            {&m.io_state_12_0, &m.io_state_12_1, &m.io_state_12_2, &m.io_state_12_3, &m.io_state_12_4, &m.io_state_12_5, &m.io_state_12_6, &m.io_state_12_7, &m.io_state_12_8, &m.io_state_12_9, &m.io_state_12_10, &m.io_state_12_11, &m.io_state_12_12, &m.io_state_12_13, &m.io_state_12_14},
            {&m.io_state_13_0, &m.io_state_13_1, &m.io_state_13_2, &m.io_state_13_3, &m.io_state_13_4, &m.io_state_13_5, &m.io_state_13_6, &m.io_state_13_7, &m.io_state_13_8, &m.io_state_13_9, &m.io_state_13_10, &m.io_state_13_11, &m.io_state_13_12, &m.io_state_13_13, &m.io_state_13_14},
            {&m.io_state_14_0, &m.io_state_14_1, &m.io_state_14_2, &m.io_state_14_3, &m.io_state_14_4, &m.io_state_14_5, &m.io_state_14_6, &m.io_state_14_7, &m.io_state_14_8, &m.io_state_14_9, &m.io_state_14_10, &m.io_state_14_11, &m.io_state_14_12, &m.io_state_14_13, &m.io_state_14_14}
        }});
}

#endif //GAME_OF_LIFE_MAP_IO_H
