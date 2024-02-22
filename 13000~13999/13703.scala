import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val Array(k, n) = input.head.split(" ").map(_.toInt)
    val dp          = Array.fill(n + 1, n + k + 1)(0L)
    dp(0)(k) = 1

    for
      i <- 0 until n
      j <- 1 to n + k
      if dp(i)(j) > 0
    do
      dp(i + 1)(j - 1) += dp(i)(j)
      dp(i + 1)(j + 1) += dp(i)(j)

    (dp(n).sum - dp(n)(0)).toString
