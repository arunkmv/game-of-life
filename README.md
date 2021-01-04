# game-of-life
This repository contains a hardware implementation of Conway's Game of Life. It is a simple cell based architecture where cell states are stored in individual registers (may not be the best architecture for large grids). The parameterized circuits are written in Chisel and can be used to generate grids of any size. 

## Requirements

- Install ``sbt``. Refer to https://www.scala-sbt.org/download.html
- Install ``verilator``. On MacOS you can install it using ``brew install verilator``. Refer to https://www.veripool.org/projects/verilator/wiki/Installing

## Running tests and simulations

### Using Chisel Tests:

```sh
$ sbt test
```

### Using Verilator:

A verilator based circuit simulator has also been implemented which can be used to visualize the circuit output. These can be built and run using ``make``.

For example, to simulate a blinker pattern on a 3*3 grid:
```sh
$ make sim-blinker
```

Other available ``make`` targets are:

- ``sim-pulsar`` - Pulsar pattern on a 15*15 grid
- ``sim-random`` - Random pattern on a 15*15 grid
- ``sim-random_large`` - Random pattern on a 40*40 grid


