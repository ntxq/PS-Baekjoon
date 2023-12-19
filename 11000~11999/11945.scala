import typings.node.{fsMod as fs}

import scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val fishBread = fs.readFileSync("/dev/stdin").toString().trim().linesIterator.drop(1).map(_.reverse).mkString("\n")
    fs.writeFileSync("/dev/stdout", fishBread)
