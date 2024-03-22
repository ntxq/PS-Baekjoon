import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*
import scala.collection.Searching.Found
import scala.collection.Searching.InsertionPoint

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def lis(xs: Array[Int]): Int =
    val dp = Array.fill(xs.length + 1)(Int.MaxValue)
    dp(0) = Int.MinValue

    for x <- xs
    do
      val idx = dp.search(x).insertionPoint
      if dp(idx - 1) < x && x < dp(idx)
      then dp(idx) = x

    dp.lastIndexWhere(_ != Int.MaxValue)

  def solve(input: List[String]): String =
    val circuits = input.tail
      .map(_.split(" ").map(_.toInt))
      .map {
        case Array(u, v) => (u, v)
        case _           => assert(false)
      }
      .sortBy(_._2)
      .map(_._1)
      .reverse
      .toArray

    lis(circuits).toString
