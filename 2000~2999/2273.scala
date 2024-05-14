import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

import scala.collection.mutable.PriorityQueue
object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    input.map(_.split(" ").map(_.toInt)) match
      case Array(n, m) :: edges =>
        val dist = Array.fill(n, n)(false)
        for Array(u, v) <- edges
        do dist(u - 1)(v - 1) = true

        for
          k <- 0 until n
          i <- 0 until n
          j <- 0 until n
        do dist(i)(j) = dist(i)(j) || (dist(i)(k) && dist(k)(j))

        val impossible = (0 until n).exists(i => dist(i)(i))
        if impossible
        then "-1\n"
        else
          (for i <- 0 until n
          yield
            val left  = 1 + (0 until n).count(j => dist(j)(i))
            val right = n - (0 until n).count(j => dist(i)(j))
            s"${left} ${right}"
          ).mkString("\n")

      case _ => assert(false)
