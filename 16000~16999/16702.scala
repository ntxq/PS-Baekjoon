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
    val dp = Array.fill(1000001)(0)
    for
      i <- 1 until 100
      j <- (i + 1) until math.sqrt(1000000 / i).ceil.toInt
      k <- (j + 1) to (1000000 / (i * j))
      if i * j * k <= 1000000
    do dp(i * j * k) += 1

    val prefixSum = dp.scanLeft(0)(_ + _)
    input.tail.map(_.toInt + 1).map(prefixSum).mkString("\n")
