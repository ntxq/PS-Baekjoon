import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

import scala.collection.mutable.PriorityQueue
object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solveCase(n: Int, k: Int, rooms: List[Array[Int]]): String =
    val dp     = Array.fill(k + 1, n, 3)(-1)
    val values = rooms.toVector.map { case Array(l, r) => (l, r) }

    dp(0)(0)(0) = values(0)._1 + values(0)._2
    dp(1)(0)(1) = values(0)._1
    dp(1)(0)(2) = values(0)._2

    for
      i <- 0 to k
      j <- 1 until n
    do
      if dp(i)(j - 1).max != -1
      then dp(i)(j)(0) = dp(i)(j - 1).max + values(j)._1 + values(j)._2

      if i > 0 && (dp(i - 1)(j - 1)(0) max dp(i - 1)(j - 1)(1)) != -1
      then dp(i)(j)(1) = (dp(i - 1)(j - 1)(0) max dp(i - 1)(j - 1)(1)) + values(j)._1

      if i > 0 && (dp(i - 1)(j - 1)(0) max dp(i - 1)(j - 1)(2)) != -1
      then dp(i)(j)(2) = (dp(i - 1)(j - 1)(0) max dp(i - 1)(j - 1)(2)) + values(j)._2

    dp(k)(n - 1).max.toString

  def solve(input: List[String]): String =
    def loop(input: List[Array[Int]], acc: List[String]): String =
      input match
        case Array(0, 0) :: Nil =>
          acc.reverse.mkString("\n")
        case Array(n, k) :: xs =>
          val (rooms, rest) = xs.splitAt(n)
          if k == 0
          then loop(rest, rooms.map(_.sum).sum.toString :: acc)
          else loop(rest, solveCase(n, k, rooms) :: acc)
        case _ =>
          assert(false)

    loop(input.map(_.split(" ").map(_.toInt)), Nil)
