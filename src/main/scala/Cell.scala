import chisel3._
import chisel3.util.PopCount

class Cell(neighbours: Int) extends Module {

  val io = IO(new Bundle{
    val valid = Input(Bool())
    val initial = Input(Bool())

    val lifeInVicinity = Input(Vec(neighbours, Bool()))
    val state = Output(Bool())
  })

  val state = Reg(Bool())
  val living = PopCount(io.lifeInVicinity.asUInt())

  when(io.valid) {
    state := io.initial
  }.otherwise {
    state := Mux(living === 2.U, state, living === 3.U)
  }

  io.state := state
}
