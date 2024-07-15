import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

case class Point(x: Int, y: Int)

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val s =
      ("#" :: (for ch <- input.head.toList
      yield s"$ch#")).mkString

    val dp = Array.fill(s.length)(0)

    def loop(idx: Int, l: Int, r: Int): Long =
      if idx == s.length
      then
        dp.zipWithIndex.foldLeft(0L) { case (acc, (x, idx)) =>
          if idx % 2 == 0 then acc + (x - 1) / 2 else acc + x / 2
        }
      else
        dp(idx) = 0 max ((r - idx) min dp(l + (r - idx)))

        while s(idx - dp(idx)) == s(idx + dp(idx)) do dp(idx) += 1

        if idx + dp(idx) > r
        then loop(idx + 1, idx - dp(idx), idx + dp(idx))
        else loop(idx + 1, l, r)

    loop(1, 1, 1).toString
