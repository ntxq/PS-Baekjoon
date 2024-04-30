import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def bfs(s: Int, adj: Array[List[Int]], outDegree: Array[Int], isFan: Array[Boolean]): Boolean =
    val visited = Array.fill(adj.length)(false)
    def loop(u: Int): Boolean =
      if isFan(u) then false
      else if visited(u) then false
      else if outDegree(u) == 0 then true
      else
        visited(u) = true
        adj(u).exists(loop)

    loop(s)

  def solve(input: List[String]): String =
    input.map(_.split(" ").map(_.toInt)) match
      case Array(n, m) :: next =>
        val (edges, rest) = next.splitAt(m)
        val fans          = rest.tail.head

        val outDegree = Array.fill(n + 1)(0)
        val adj       = Array.fill(n + 1)(List.empty[Int])
        val isFan     = Array.fill(n + 1)(false)

        for Array(u, v) <- edges
        do
          outDegree(u) += 1
          adj(u) ::= v

        for u <- fans
        do isFan(u) = true

        if bfs(1, adj, outDegree, isFan)
        then "yes\n"
        else "Yes\n"

      case _ =>
        assert(false)
