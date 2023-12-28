import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.drop(1).toList.head.split(" ").map(_.toInt)
    val output = getExpectedTime(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def getExpectedTime(input: Array[Int]): Double =
    input.sorted(using Ordering.Int.reverse).zipWithIndex.foldLeft(0.0) { case (acc, (time, index)) =>
      acc + time / Math.pow(2, index + 1)
    }
