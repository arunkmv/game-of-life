package gol

import chipsalliance.rocketchip.config.Parameters
import chisel3._
import freechips.rocketchip.regmapper.{HasRegMap, RegField}

case class GameOfLifeParams(
  address: BigInt = 0x2000,
  gridX: Int = 100,
  gridY: Int = 100
)

trait GameOfLifeModule extends HasRegMap {

  implicit val p: Parameters
  def params: GameOfLifeParams
  val clock: Clock
  val reset: Reset

  val x_addr = Reg(UInt(32.W))
  val y_addr = Reg(UInt(32.W))

  val impl = Module(new Universe(params.gridX, params.gridY))

  impl.clock := clock
  impl.reset := reset

  impl.io.x_addr := x_addr
  impl.io.y_addr := y_addr

  regmap(
    0x00 -> Seq(
      RegField.r(1, impl.io.running)),
    0x04 -> Seq(
      RegField.w(32, x_addr)),
    0x08 -> Seq(
      RegField.w(32, y_addr)),
    0xC -> Seq(
      RegField.w(1, impl.io.write_enable)),
    0xD -> Seq(
      RegField.w(1, impl.io.write_state)),
    0xE -> Seq(
      RegField.w(1, impl.io.pause)),
    0xF -> Seq(
      RegField.r(1, impl.io.state))
    )
}
