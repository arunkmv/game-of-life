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

  def inBounds(i: (Int, Int)): Boolean = i match {
    case (x, y) => (x < gridX) && (x >= 0) && (y < gridY) && (y >= 0)
  }

  def neighbourIndices(x: Int, y: Int): List[(Int, Int)] = {
    def vicinityCoordinates(i: Int) = List(i - 1, i, i + 1)
    vicinityCoordinates(y).flatMap(b => vicinityCoordinates(x).map(a => (a, b))).filterNot(_ == (x, y))
  }

  val running = RegInit(true.B)
  io.running := running

  when(io.pause) {
    running := ~running
  }

  val cells: Seq[Seq[Cell]] =
    (0 until gridY).map(y =>
      (0 until gridX).map(x =>
        Module(new Cell(neighbourIndices(x, y).filter(inBounds)))))

  for { y <- 0 until gridY
        x <- 0 until gridX
        cell = cells(y)(x)
  } {
    cell.io.write_enable := (io.y_addr === y.U) && (io.x_addr === x.U) && io.write_enable
    cell.io.write_state := io.write_state
    cell.io.running := running
    cell.neighbours.zipWithIndex.foreach {
      case ((a, b), n) => cell.io.lifeInVicinity(n) := cells(b)(a).io.state
    }
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
