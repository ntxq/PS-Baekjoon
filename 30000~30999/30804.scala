import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val n      = input.head.toInt
    val fruits = input.tail.head.split(" ").map(_.toInt)

    (for
      x <- 1 to 9
      y <- (x + 1) to 9
    yield
      val (curLen, maxLen) = fruits.foldLeft((0, 0)) { case ((curLen, maxLen), fruit) =>
        if fruit == x || fruit == y then (curLen + 1, maxLen)
        else (0, maxLen max curLen)
      }
      curLen max maxLen
    ).max.toString
