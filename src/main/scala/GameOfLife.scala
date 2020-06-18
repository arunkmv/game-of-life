package gol

import freechips.rocketchip.regmapper.HasRegMap

case class GameOfLifeParams(
  gridX: Int = 100,
  gridY: Int = 100
)

trait GameOfLifeModule extends HasRegMap {

}
