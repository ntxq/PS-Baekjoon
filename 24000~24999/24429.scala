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
    val n = input.head.toInt

    val board =
      for row <- input.tail.take(n).map(_.split(" ").map(_.toInt)).toArray
      yield row

    val targets = input
      .drop(n + 2)
      .map(_.split(" ").map(_.toInt))
      .map { case Array(x, y) =>
        (x, y)
      }
      .sortBy { case (x, y) => x + y }

    val dp = Array.fill(n + 1, n + 1)(0)

    def travel(curpos: (Int, Int), target: (Int, Int)): Unit =
      for
        i <- curpos._1 to target._1
        j <- curpos._2 to target._2
      do dp(i)(j) = board(i - 1)(j - 1) + (dp(i - 1)(j) max dp(i)(j - 1))

    def loop(curpos: (Int, Int), targets: List[(Int, Int)]): Int =
      targets match
        case Nil =>
          travel(curpos, (n, n))
          dp(n)(n)
        case target :: rest =>
          if target._1 < curpos._1 || target._2 < curpos._2
          then -1
          else
            travel(curpos, target)
            loop(target, rest)

    loop((1, 1), targets).toString
