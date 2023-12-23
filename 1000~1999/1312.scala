import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.split(" ").toList.map(_.toInt)
    val output = getNthDiv(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def getNthDiv(input: List[Int]): Int =
    input match
      case List(a, b, n) =>
        def loop(a: Int, b: Int, n: Int): Int =
          if a % b == 0
          then 0
          else if n == 0
          then a * 10 / b
          else loop(a * 10 % b, b, n - 1)
        loop(if a > b then a % b else a, b, n - 1)
      case _ => -1
