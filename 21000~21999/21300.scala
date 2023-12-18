import typings.node.{fsMod as fs}

import scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val deposit = fs.readFileSync("/dev/stdin").toString().trim().split(" ").map(_.toInt).map(_ * 5).sum
    fs.writeFileSync("/dev/stdout", s"$deposit\n")
