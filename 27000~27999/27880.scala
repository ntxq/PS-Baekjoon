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
    input
      .map(_.split(" "))
      .map { case Array(name, count) => (name, count.toInt) }
      .foldLeft(0) {
        case (acc, ("Es", count))    => acc + count * 21
        case (acc, ("Stair", count)) => acc + count * 17
      }
      .toString
