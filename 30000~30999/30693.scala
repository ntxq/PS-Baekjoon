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
    val brackets = input.tail.head.toList

    def loop(s: List[Char], acc: Int, curLen: Int, curDepth: Int): Int =
      s match
        case Nil =>
          if curDepth == 0 && curLen == 0
          then acc
          else -1
        case '(' :: rest =>
          val newDepth = curDepth + 1
          if newDepth == 0
          then loop(rest, acc + curLen + 1, 0, newDepth)
          else if newDepth < 0
          then loop(rest, acc, curLen + 1, newDepth)
          else loop(rest, acc, 0, newDepth)
        case ')' :: rest =>
          val newDepth = curDepth - 1
          if newDepth == 0
          then loop(rest, acc, 0, newDepth)
          else if newDepth < 0
          then loop(rest, acc, curLen + 1, newDepth)
          else loop(rest, acc, 0, newDepth)
        case _ :: rest =>
          assert(false)

    loop(brackets, 0, 0, 0).toString
