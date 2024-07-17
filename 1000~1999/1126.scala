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
    val blocks = input(1).split(" ").map(_.toInt)

    val dp = Array.fill(n, 500001)(Int.MinValue)

    dp(0)(0) = 0
    dp(0)(blocks(0)) = blocks(0)

    for
      i <- 1 until n
      block = blocks(i)
      j <- 0 until 500001
    do
      dp(i)(j) = dp(i - 1)(j) max
        (if j + block <= 500000 then dp(i - 1)(j + block) else Int.MinValue) max
        (if j - block >= 0
         then dp(i - 1)(j - block) + block
         else dp(i - 1)(block - j) + j)

    if dp(n - 1)(0) == 0 then "-1"
    else dp(n - 1)(0).toString
