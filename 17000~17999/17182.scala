import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def backtrack(curIdx: Int, toVisit: Int, acc: Int, dists: Array[Array[Int]], visited: Array[Boolean]): Int =
    if toVisit == 0
    then acc
    else
      (for
        j <- dists.indices
        if !visited(j)
      yield
        visited(j) = true
        val res = backtrack(j, toVisit - 1, acc + dists(curIdx)(j), dists, visited)
        visited(j) = false
        res
      ).min

  def solve(input: List[String]): String =
    input.map(_.split(" ").map(_.toInt)) match
      case Array(n, s) :: dists =>
        val dist = Array.ofDim[Int](n, n)
        for
          (ds, i) <- dists.zipWithIndex
          (d, j)  <- ds.zipWithIndex
        do dist(i)(j) = d

        for
          k <- 0 until n
          i <- 0 until n
          j <- 0 until n
          if dist(i)(j) > dist(i)(k) + dist(k)(j)
        do dist(i)(j) = dist(i)(k) + dist(k)(j)

        val visited = Array.fill(n)(false)
        visited(s) = true
        backtrack(s, n - 1, 0, dist, visited).toString

      case _ =>
        assert(false)
