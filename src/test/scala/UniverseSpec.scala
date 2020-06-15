import chisel3._
import chiseltest._
import gol.Universe
import org.scalatest._

class UniverseSpec extends FlatSpec with ChiselScalatestTester with Matchers {

  def UniverseTest(gridX: Int, gridY: Int, initial: Seq[Seq[Int]], expected: Seq[Seq[Seq[Int]]]): Unit = {
    def playOneGen(c: Universe) = {
      c.io.pause.poke(true.B)
      c.clock.step(2)
      c.io.pause.poke(false.B)
    }

    test(new Universe(gridX, gridY)) { c =>
      c.io.pause.poke(true.B)
      c.clock.step(1)
      c.io.pause.poke(false.B)

      c.io.write_enable.poke(true.B)

      initial.zipWithIndex.foreach(i => i._1.zipWithIndex.foreach(j => {
        c.io.y_addr.poke(i._2.U)
        c.io.x_addr.poke(j._2.U)
        c.io.write_state.poke(j._1.B)
        c.clock.step(1)
      }))
      c.io.write_enable.poke(false.B)

      for (expectedState <- expected) {
        playOneGen(c)
        expectedState.zipWithIndex.foreach(i =>
          i._1.zipWithIndex.foreach(j => {
            c.io.y_addr.poke(i._2.U)
            c.io.x_addr.poke(j._2.U)
            c.io.state.expect(j._1.B)
            c.clock.step(1)
          }))
      }
    }
  }

  it should "form block pattern" in {
    val block = Seq(
      Seq(1, 1),
      Seq(1, 1))

    UniverseTest(2, 2, block, Seq.fill(3) {block})
  }

  it should "form blinker pattern" in {
    val blinkerPhase1 = Seq(
      Seq(0, 0, 0),
      Seq(1, 1, 1),
      Seq(0, 0, 0))

    val blinkerPhase2 = Seq(
      Seq(0, 1, 0),
      Seq(0, 1, 0),
      Seq(0, 1, 0))

    UniverseTest(3, 3, blinkerPhase1, Seq(blinkerPhase2, blinkerPhase1, blinkerPhase2))
  }

  it should "form bee-hive pattern" in {
    val beehive = Seq(
      Seq(0, 1, 1, 0),
      Seq(1, 0, 0, 1),
      Seq(0, 1, 1, 0))

    UniverseTest(4, 3, beehive, Seq.fill(3) {beehive})
  }

  it should "form toad pattern" in {
    val toadPhase1 = Seq(
      Seq(0, 0, 0, 0),
      Seq(0, 1, 1, 1),
      Seq(1, 1, 1, 0),
      Seq(0, 0, 0, 0))

    val toadPhase2 = Seq(
      Seq(0, 0, 1, 0),
      Seq(1, 0, 0, 1),
      Seq(1, 0, 0, 1),
      Seq(0, 1, 0, 0))

    UniverseTest(4, 4, toadPhase1, Seq(toadPhase2, toadPhase1, toadPhase2))
  }

  it should "form pulsar pattern" in {
    val pulsarPhase1 = Seq(
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0),
      Seq(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0),
      Seq(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0),
      Seq(0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0),
      Seq(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0),
      Seq(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0),
      Seq(0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))

    val pulsarPhase2 = Seq(
      Seq(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1),
      Seq(0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0),
      Seq(0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0),
      Seq(0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0),
      Seq(1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
      Seq(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0))

    val pulsarPhase3 = Seq(
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0),
      Seq(0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0),
      Seq(0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0),
      Seq(0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0),
      Seq(0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0),
      Seq(0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
      Seq(0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0),
      Seq(0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0),
      Seq(0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0),
      Seq(0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0),
      Seq(0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0),
      Seq(0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0),
      Seq(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))

    UniverseTest(15, 15, pulsarPhase1, Seq(pulsarPhase2, pulsarPhase3, pulsarPhase1))
  }
}