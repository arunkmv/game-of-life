name := "game-of-life"

version := "0.1"

scalaVersion := "2.12.11"

scalacOptions ++= Seq("-Xsource:2.11")

val defaultVersions = Map(
  "chisel3" -> "3.4.0",
  "chiseltest" -> "0.3.0",
  "rocketchip" -> "1.2.0"
)

addCompilerPlugin("edu.berkeley.cs" % "chisel3-plugin" % defaultVersions("chisel3") cross CrossVersion.full)

libraryDependencies ++= Seq("chisel3", "chiseltest", "rocketchip").map {
  dep: String => "edu.berkeley.cs" %% dep % sys.props.getOrElse(dep + "Version", defaultVersions(dep))
}
