import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.drop(1).toList.map(_.toInt)
    val output = getMaxGroupSize(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def getMaxGroupSize(input: List[Int]): Int =
    def update(cow: Int, acc: List[Int]): List[Int] =
      acc match
        case x :: xs =>
          if cow < 10
          then (cow + x) :: xs
          else (cow % 10 + x) :: update(cow / 10, xs)
        case Nil => acc

    def loop(cows: List[Int], acc: List[Int], count: Int): Int =
      cows match
        case cow :: rest =>
          val nAcc = update(cow, acc)
          if nAcc.forall(_ < 10)
          then loop(rest, nAcc, count + 1) max loop(rest, acc, count)
          else loop(rest, acc, count)
        case Nil => count

    loop(input, List.fill(9)(0), 0)
