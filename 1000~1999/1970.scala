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
    val drinks = input(1).split(" ").map(_.toInt)

    val dp = Array.fill(n, n)(0)

    for
      len <- 1 until n
      i   <- 0 until n - len
      j = i + len
    do
      if drinks(i) == drinks(j)
      then dp(i)(j) = dp(i + 1)(j - 1) + 1

      for k <- i until j
      do dp(i)(j) = dp(i)(j) max (dp(i)(k) + dp(k + 1)(j))

    dp(0)(n - 1).toString
