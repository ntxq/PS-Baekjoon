import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def handleCase(numbers: Array[Int]): String =
    val sums =
      (for
        x <- numbers.indices
        y <- (x + 1 to numbers.length - 1)
      yield (numbers(x) + numbers(y), x, y)).sorted.toList

    val diffs =
      (for
        x <- numbers.indices
        y <- (x + 1 to numbers.length - 1)
        z <- List((numbers(x) - numbers(y), x, y), (numbers(y) - numbers(x), y, x))
      yield z).sorted.toList

    def loop(sums: List[(Int, Int, Int)], diffs: List[(Int, Int, Int)], acc: Int): String =
      (sums, diffs) match
        case (Nil, _) | (_, Nil) =>
          acc match
            case -536870913 => "no solution"
            case x          => x.toString
        case ((sum, a, b) :: ss, (diff, d, c) :: ds) if sum == diff =>
          if a == c || a == d || b == c || b == d then loop(sums, ds, acc)
          else loop(sums, ds, acc max numbers(d))
        case (((sum, _, _) :: ss), ((diff, _, _) :: ds)) =>
          if sum < diff then loop(ss, diffs, acc)
          else loop(sums, ds, acc)

    loop(sums, diffs, -536870913)

  def solve(input: List[String]): String =
    def loop(input: List[Int], acc: List[String]): String =
      input match
        case List(0) | Nil => acc.reverse.mkString("\n")
        case n :: xs =>
          val (testcase, rest) = xs.splitAt(n)
          loop(rest, handleCase(testcase.toArray) :: acc)

    loop(input.map(_.toInt), Nil)
