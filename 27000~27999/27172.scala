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
    val isPresent = Array.fill(1000001)(false)
    val scores    = Array.fill(1000001)(0)

    val n    = input.head.toInt
    val nums = input.tail.head.split(" ").map(_.toInt)

    for x <- nums
    do isPresent(x) = true

    for
      x   <- nums
      mul <- (2 * x to 1000000 by x)
      if isPresent(mul)
    do
      scores(x) += 1
      scores(mul) -= 1

    (for x <- nums
    yield scores(x)).mkString(" ")
