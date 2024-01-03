import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = electChairman(input).mkString("\n")
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def electChairman(input: List[String]): List[String] =
    input match
      case Nil => Nil
      case n :: edges =>
        val num  = n.toInt
        val dist = Array.fill(num, num)(Int.MaxValue / 2)

        for
          Array(u, v) <- edges.map(_.split(" ").map(_.toInt))
          if u != v
        do
          dist(u - 1)(v - 1) = 1
          dist(v - 1)(u - 1) = 1

        for i <- 0 until num
        do dist(i)(i) = 0

        for
          k <- 0 until num
          i <- 0 until num
          j <- 0 until num
        do dist(i)(j) = Math.min(dist(i)(j), dist(i)(k) + dist(k)(j))

        val minDists = dist.map(_.max)
        val minDist  = minDists.min

        val candidates = minDists.zipWithIndex.filter(_._1 == minDist).map(_._2 + 1)
        List(s"$minDist ${candidates.length}", candidates.mkString(" "))
