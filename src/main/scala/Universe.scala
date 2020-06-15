package gol

import chisel3._

class Universe(gridX: Int, gridY: Int) extends Module {

  val io = IO(new Bundle {
    val seedState = Input(Vec(gridY, Vec(gridX, Bool())))
    val valid = Input(Bool())

    val state = Output(Vec(gridY, Vec(gridX, Bool())))
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

  def n(x: Int) = x < gridX

  def e(y: Int) = y < gridY

  def s(x: Int) = x >= 0

  def w(y: Int) = y >= 0

  def inBounds(x: Int, y: Int): Boolean = n(x) && s(x) && e(y) && w(y)

  def neighbourIndices(x: Int, y: Int): Seq[(Int, Int)] = {
    def vicinityCoords(i: Int) = Seq(i - 1, i, i + 1)
    vicinityCoords(y).flatMap(a => vicinityCoords(x).map(b => (a, b))).filterNot(_ == (y, x))
  }

  def countNeighbours(x: Int, y: Int): Int =
    neighbourIndices(x, y).map(i => inBounds(i._2, i._1)).count(i => i)

  val cells: Seq[Seq[Cell]] =
    Seq.range(0, gridY).map(y =>
      Seq.range(0, gridX).map(x =>
        Module(new Cell(countNeighbours(x, y)))))

  for {  y <- 0 until gridY
         x <- 0 until gridX
         cell = cells(y)(x)
  } {
    cell.io.write_enable := io.valid
    cell.io.write_state := io.seedState(y)(x)
    cell.io.running := true.B
    neighbourIndices(x, y).filter(i => inBounds(i._2, i._1))
      .zipWithIndex.foreach(j => cell.io.lifeInVicinity(j._2) := cells(j._1._1)(j._1._2).io.state)

    io.state(y)(x) := cell.io.state
  }

  //printState()
}
