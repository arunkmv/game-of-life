package gol

object Sims {

  class Sim_3x3   extends Universe( 3,  3)
  class Sim_15x15 extends Universe(15, 15)
  class Sim_40x40 extends Universe(40, 40)

  def main(args: Array[String]): Unit = {
    val testArgs = args.slice(1, args.length)
    args(0) match {
      case "3x3" =>
        (new chisel3.stage.ChiselStage).emitVerilog(new Sim_3x3, testArgs)
      case "15x15" =>
        (new chisel3.stage.ChiselStage).emitVerilog(new Sim_15x15, testArgs)
      case "40x40" =>
        (new chisel3.stage.ChiselStage).emitVerilog(new Sim_40x40, testArgs)

    }
  }
}