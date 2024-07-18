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
    val n = input.head.toInt

    val grundyNums = Array.ofDim[Int](n + 1)
    grundyNums(0) = 0
    grundyNums(1) = 0
    grundyNums(2) = 1

    for i <- 3 to n
    do
      val curGrundy = Array.fill(n + 1)(false)

      for j <- 0 to i / 2
      do
        val left  = j
        val right = i - j - 2
        curGrundy(grundyNums(left) ^ grundyNums(right)) = true

      grundyNums(i) = curGrundy.indexWhere(!_)

    if grundyNums(n) == 0 then "2" else "1"
