import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*
import scala.collection.Searching.Found
import scala.collection.Searching.InsertionPoint

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val Array(xApple, xOrange) = input.head.split(" ").map(_.toInt)
    val Array(yApple, yOrange) = input(1).split(" ").map(_.toInt)

    ((xApple + yOrange) min (yApple + xOrange)).toString
      