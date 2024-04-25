import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def splitTestcases(input: List[(Int, Int, Int)]): List[List[(Int, Int, Int)]] =
    def loop(
        input: List[(Int, Int, Int)],
        acc: List[List[(Int, Int, Int)]]
    ): List[List[(Int, Int, Int)]] =
      input match
        case Nil             => acc.reverse
        case (0, 0, 0) :: ts => loop(ts, acc)
        case (n, a, b) :: ts =>
          val (testcase, rest) = ts.splitAt(n)
          loop(rest, ((n, a, b) :: testcase) :: acc)

    loop(input, Nil)

  def solve(input: List[String]): String =
    val teams = input.map(_.split(" ").map(_.toInt)).map { case Array(a, b, c) => (a, b, c) }
    (for testcase <- splitTestcases(teams)
    yield solveCase(testcase)).mkString("\n")

  def solveCase(testcase: List[(Int, Int, Int)]): Int =
    testcase match
      case (n, a, b) :: teams =>
        def loop(teams: List[(Int, Int, Int)], a: Int, b: Int, acc: Int): Int =
          (teams, a, b) match
            case (Nil, _, _) => acc
            case ((0, _, _) :: ts, _, _) =>
              loop(ts, a, b, acc)
            case ((n, da, _) :: ts, a, 0) =>
              loop(ts, a - n, b, acc + n * da)
            case ((n, _, db) :: ts, 0, b) =>
              loop(ts, a, b - n, acc + n * db)
            case ((n, da, db) :: ts, a, b) =>
              if da < db then
                val cnt = n min a
                loop((n - cnt, da, db) :: ts, a - cnt, b, acc + cnt * da)
              else
                val cnt = n min b
                loop((n - cnt, da, db) :: ts, a, b - cnt, acc + cnt * db)
        loop(teams.sortBy(t => (t._2 - t._3).abs)(using Ordering[Int].reverse), a, b, 0)

      case _ =>
        assert(false)
