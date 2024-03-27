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
    input.map(_.split(" ").map(_.toInt)) match
      case Array(n, q) :: tokens :: events =>
        val prefixSum = tokens.scanLeft(0L)(_ + _)
        val resets    = scala.collection.mutable.TreeSet.empty[Int]

        def loop(tokens: List[Array[Int]], acc: List[Long]): List[Long] =
          tokens match
            case Nil =>
              acc.reverse
            case Array(1, day) :: ts =>
              resets += day
              loop(ts, acc)
            case Array(2, s, e) :: ts =>
              resets.maxBefore(e) match
                case Some(reset) if s <= reset =>
                  val sum = prefixSum(e) - prefixSum(reset)
                  loop(ts, sum :: acc)
                case _ =>
                  val sum = prefixSum(e) - prefixSum(s - 1)
                  loop(ts, sum :: acc)
            case _ =>
              assert(false)

        loop(events, Nil).mkString("\n")

      case _ =>
        assert(false)
