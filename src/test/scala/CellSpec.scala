import chisel3._
import chiseltest._
import org.scalatest._
import gol.Cell

class CellSpec extends FlatSpec with ChiselScalatestTester with Matchers {

  def CellTest(neighbours: Int, initial: Boolean, aliveNeighbours: Int, expected: Boolean): Unit = {
    val lifeInVicinity: Seq[Bool] = Seq.fill(aliveNeighbours) {
      true.B
    } ++ Seq.fill(neighbours - aliveNeighbours) {
      false.B
    }
    test(new Cell(neighbours)) { c =>
      c.io.initial.poke(initial.B)
      c.io.valid.poke(true.B)
      c.clock.step(1)
      c.io.valid.poke(false.B)
      lifeInVicinity.zipWithIndex.foreach(i => c.io.lifeInVicinity(i._2).poke(i._1))
      c.clock.step(1)
      c.io.state.expect(expected.B)
    }
  }

  it should "living die to under population" in {
    CellTest(8, true, 0, false)
    CellTest(8, true, 1, false)
  }

  it should "living continue to live" in {
    CellTest(8, true, 2, true)
    CellTest(8, true, 3, true)
  }

  it should "living die to over population" in {
    CellTest(8, true, 4, false)
    CellTest(8, true, 5, false)
    CellTest(8, true, 6, false)
    CellTest(8, true, 7, false)
    CellTest(8, true, 8, false)
  }

  it should "dead stay dead" in {
    CellTest(8, false, 0, false)
    CellTest(8, false, 1, false)
    CellTest(8, false, 2, false)
    CellTest(8, false, 4, false)
    CellTest(8, false, 5, false)
    CellTest(8, false, 6, false)
    CellTest(8, false, 7, false)
    CellTest(8, false, 8, false)
  }

  it should "dead come to life" in {
    CellTest(8, false, 3, true)
  }
}
