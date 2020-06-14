package gol

object Sims {

  class Sim_3x3   extends Universe( 3,  3)
  class Sim_15x15 extends Universe(15, 15)

  def main(args: Array[String]): Unit = {
    val testArgs = args.slice(1, args.length)
    args(0) match {
      case "3x3" => chisel3.Driver.execute(
        testArgs, () => new Sim_3x3)
      case "15x15" => chisel3.Driver.execute(
        testArgs, () => new Sim_15x15)
    }
  }
}