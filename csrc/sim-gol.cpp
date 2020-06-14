#include <stdio.h>

int main() {
    dut module;

    initialize_dut(module);

    size_t gen = 0;

    for (size_t i = 0; i < 10; i++) {
        module.reset = 1;
        module.clock = 0;
        module.eval();
        module.clock = 1;
        module.eval();
    }
    module.reset = 0;

    initialize_state(module);

    for (size_t cycle = 0;; cycle++) {

        module.clock = 0;
        module.eval();

        system("clear");
        display_state(module, gen);
        usleep(500000);

        module.clock = 1;
        module.eval();

        gen++;
    }
}