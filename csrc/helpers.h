#ifndef GAME_OF_LIFE_HELPERS
#define GAME_OF_LIFE_HELPERS

#include "dut.h"
#include <array>

static void step(dut &m, int times = 1) {
    for (int i = 0; i < times; i++) {
        m.clock = 0;
        m.eval();
        m.clock = 1;
        m.eval();
    }
}

template<size_t gridX, size_t gridY>
static void poke(std::array <std::array<unsigned char, gridX>, gridY> pattern, dut &m) {

    m.io_pause = 1;
    step(m);
    m.io_pause = 0;
    m.io_write_enable = 1;
    step(m);

    for (int i = 0; i < gridY; i++) {
        for (int j = 0; j < gridX; j++) {
            m.io_y_addr = i;
            m.io_x_addr = j;
            m.io_write_state = pattern[i][j];
            step(m);
        }
    }

    m.io_write_enable = 0;
    m.eval();
}

template<size_t gridX, size_t gridY>
static void peek(dut &m) {
    for (int i = gridY - 1; i >= 0; i--) {
        for (int j = gridX - 1; j >= 0; j--) {
            m.io_y_addr = i;
            m.io_x_addr = j;
            step(m);
            if (m.io_state == 1)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

#endif //GAME_OF_LIFE_HELPERS
