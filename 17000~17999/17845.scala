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
    val Array(n, k) = input.head.split(" ").map(_.toInt)

    val knapsack = Array.fill(n + 1)(0)
    for
      Array(weight, cost) <- input.tail.map(_.split(" ").map(_.toInt))
      i                   <- (cost to n).reverse
    do knapsack(i) = knapsack(i) max (knapsack(i - cost) + weight)

    knapsack.last.toString
