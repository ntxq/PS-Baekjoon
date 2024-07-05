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
    val yard      = input.tail.head.split(" ").map(_.toInt)
    val prefixSum = Array.fill(yard.length + 1)(0)

    for Array(a, b, k) <- input.tail.tail.map(_.split(" ").map(_.toInt))
    do
      prefixSum(a - 1) += k
      prefixSum(b) -= k

    for i <- 1 until prefixSum.length do prefixSum(i) += prefixSum(i - 1)

    yard.indices.map(i => yard(i) + prefixSum(i)).mkString(" ")
