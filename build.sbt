name := "game-of-life"

version := "0.1"

scalaVersion := "2.12.11"

scalacOptions ++= Seq("-Xsource:2.11")

val defaultVersions = Map(
  "chisel3" -> "3.3.+",
  "chiseltest" -> "0.2.+",
  "rocketchip" -> "1.2.0"
)

libraryDependencies ++= Seq("chisel3", "chiseltest", "rocketchip").map {
  dep: String => "edu.berkeley.cs" %% dep % sys.props.getOrElse(dep + "Version", defaultVersions(dep))
}