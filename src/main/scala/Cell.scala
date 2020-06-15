package gol

import chisel3._
import chisel3.util.{MuxCase, PopCount}

class Cell(neighbours: Int) extends Module {

  val io = IO(new Bundle{
    val running        = Input(Bool())
    val write_enable   = Input(Bool())
    val write_state    = Input(Bool())
    val lifeInVicinity = Input(Vec(neighbours, Bool()))

    val state = Output(Bool())
  })

  val state = Reg(Bool())
  val living = PopCount(io.lifeInVicinity.asUInt())

  val two_alive    = living === 2.U
  val three_alive  = living === 3.U

  state := MuxCase(state, Seq(
    io.write_enable       -> io.write_state,
    (io.running &  state) -> (two_alive | three_alive),
    (io.running & !state) -> three_alive
  ))

  io.state := state
}
