package gol

import chisel3._
import chisel3.util.MuxLookup

class Universe(gridX: Int, gridY: Int) extends Module {

  val io = IO(new Bundle {
    val x_addr       = Input(UInt(32.W))
    val y_addr       = Input(UInt(32.W))
    val write_enable = Input(Bool())
    val write_state  = Input(Bool())

    val pause = Input(Bool())     //Trigger to toggle running(play/pause)

    val running = Output(Bool())
    val state   = Output(Bool())
  })

  def printState(): Unit = {
    printf("--------\n")
    for (y <- (0 until gridY).reverse) {
      for (x <- 0 until gridX) {
        printf(p"${cells(y)(x).io.state}")
      }
      printf("\n")
    }
  }

  def inBounds(x: Int, y: Int): Boolean = (x < gridX) && (x >= 0) && (y < gridY) && (y >= 0)

  def neighbourIndices(x: Int, y: Int): Seq[(Int, Int)] = {
    def vicinityCoords(i: Int) = Seq(i - 1, i, i + 1)
    vicinityCoords(y).flatMap(a => vicinityCoords(x).map(b => (a, b))).filterNot(_ == (y, x))
  }

  def countNeighbours(x: Int, y: Int): Int =
    neighbourIndices(x, y).map(i => inBounds(i._2, i._1)).count(i => i)

  val running = RegInit(true.B)
  io.running := running

  when(io.pause) {
    running := ~running
  }

  val cells: Seq[Seq[Cell]] =
    (0 until gridY).map(y =>
      (0 until gridX).map(x =>
        Module(new Cell(countNeighbours(x, y)))))

  for { y <- 0 until gridY
        x <- 0 until gridX
        cell = cells(y)(x)
  } {
    cell.io.write_enable := (io.y_addr === y.U) && (io.x_addr === x.U) && io.write_enable
    cell.io.write_state  := io.write_state
    cell.io.running := running
    neighbourIndices(x, y).filter(i => inBounds(i._2, i._1))
      .zipWithIndex.foreach(j => cell.io.lifeInVicinity(j._2) := cells(j._1._1)(j._1._2).io.state)
  }

  //TODO Single cell state readable per clock - heavy toll to get entire grid state
  // Use a different read architecture - stream or parallel wires (Vec(Vec))
  io.state :=
    MuxLookup(io.y_addr, false.B,
      (0 until gridY).map(y =>
        y.U -> MuxLookup(io.x_addr, false.B,
          (0 until gridX).map(x =>
            x.U -> cells(y)(x).io.state))))

  //printState()
}
