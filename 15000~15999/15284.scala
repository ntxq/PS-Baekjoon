import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val Array(a, b, c) = input.head.split(" ").map(_.toInt)
    val Array(w, h)    = input.tail.head.split(" ").map(_.toInt)

    def check_box(a: Int, b: Int, c: Int, w: Int, h: Int): Boolean =
      ((2 * a + 2 * b <= h) && (c + 2 * a <= w))
        || ((a + c <= h) && (3 * b + a + c <= w))

    check_box(a, b, c, w, h) || check_box(a, b, c, h, w) || check_box(a, c, b, w, h)
      || check_box(a, c, b, h, w) || check_box(b, a, c, w, h) || check_box(b, a, c, h, w)
      || check_box(b, c, a, w, h) || check_box(b, c, a, h, w) || check_box(c, a, b, w, h)
      || check_box(c, a, b, h, w) || check_box(c, b, a, w, h) || check_box(c, b, a, h, w) match
      case true  => "Yes"
      case false => "No"
