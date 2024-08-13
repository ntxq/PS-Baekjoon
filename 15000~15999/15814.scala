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
    val s = input(0).toCharArray()

    for Array(i, j) <- input.drop(2).map(_.split(" ").map(_.toInt))
    do
      val tmp = s(i)
      s(i) = s(j)
      s(j) = tmp

    s.mkString
