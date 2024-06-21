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

    def loop(input: List[Int], stack: List[(Int, Int)], acc: List[String]): String =
      (input, stack) match
        case (Nil, List(_)) =>
          (("DA") :: acc.reverse).mkString("\n")
        case (_, (x1, y1) :: (x2, y2) :: rest) if x1 == y2 + 1 =>
          loop(input, (x2, y1) :: rest, s"${x2} ${y1}" :: acc)
        case (_, (x1, y1) :: (x2, y2) :: rest) if y1 == x2 - 1 =>
          loop(input, (x1, y2) :: rest, s"${x1} ${y2}" :: acc)
        case (Nil, _) =>
          "NE"
        case (x :: xs, _) =>
          loop(xs, (x, x) :: stack, acc)
    loop(input.tail.flatMap(_.split(" ").map(_.toInt)).toList, Nil, Nil)
