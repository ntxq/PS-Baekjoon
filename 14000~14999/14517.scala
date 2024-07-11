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
    val s = input.head

    val dp = Array.fill(s.length, s.length)(0)

    for i <- 0 until s.length
    do dp(i)(i) = 1

    for i <- 0 until s.length - 1
    do dp(i)(i + 1) = if s(i) == s(i + 1) then 3 else 2

    for
      len <- 3 to s.length
      i   <- 0 until s.length - len + 1
      j = i + len - 1
    do
      dp(i)(j) =
        if s(i) == s(j)
        then dp(i + 1)(j) + dp(i)(j - 1) + 1
        else dp(i + 1)(j) + dp(i)(j - 1) - dp(i + 1)(j - 1)
      dp(i)(j) %= 10007

    ((dp(0)(s.length - 1) + 10007) % 10007).toString
