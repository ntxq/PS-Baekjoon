import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*
import scala.collection.Searching.Found
import scala.collection.Searching.InsertionPoint

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def countFive(n: BigInt): BigInt =
    def loop(n: BigInt, acc: BigInt, five: BigInt): BigInt =
      if five > n
      then acc
      else loop(n, acc + n / five, five * 5)
    loop(n, 0, 5)

  def solve(input: List[String]): String =
    val n = input.head.toInt

    def loop(left: BigInt, right: BigInt): BigInt =
      if left + 1 >= right
      then
        if countFive(right) == n
        then right
        else -1
      else
        val mid = (left + right) / 2
        val cnt = countFive(mid)
        if cnt < n
        then loop(mid, right)
        else loop(left, mid)

    loop(1, BigInt(5) * n + 1).toString
