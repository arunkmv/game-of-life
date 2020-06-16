#include <stdio.h>
#include "helpers.h"

int main() {
    dut module;

    initialize_dut(module);

    size_t gen = 0;

    for (size_t i = 0; i < 10; i++) {
        module.reset = 1;
        step(module);
    }
    module.reset = 0;

    initialize_state(module);

    for (size_t cycle = 0;; cycle++) {

        //Runs the simulation for one generation and pauses it back again to display
        module.io_pause = 1;
        step(module, 2);
        module.io_pause = 0;
        step(module);

        system("clear");
        display_state(module, gen);
        usleep(500000);

        gen++;
    }
}