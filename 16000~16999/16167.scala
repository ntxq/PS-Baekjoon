import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def dijkstra(s: Int, adj: Array[List[(Int, Int)]]): (Int, Int) =
    val pq   = collection.mutable.PriorityQueue.empty[(Int, Int)](using Ordering[Int].on[(Int, Int)](_._1).reverse)
    val cost = Array.fill(adj.length)(Int.MaxValue)
    val dist = Array.fill(adj.length)(Int.MaxValue)

    pq.enqueue((0, s))
    cost(s) = 0
    dist(s) = 1

    while pq.nonEmpty do
      val (_, u) = pq.dequeue()
      val d      = dist(u)
      val c      = cost(u)

      for
        (v, w) <- adj(u)
        newCost = c + w
        newDist = d + 1
        if newCost < cost(v) || (newCost == cost(v) && newDist < dist(v))
      do
        pq.enqueue((newCost, v))
        cost(v) = newCost
        dist(v) = newDist

    (cost.last, dist.last)

  def solve(input: List[String]): String =
    input.map(_.split(" ").map(_.toInt)) match
      case Array(n, m) :: edges =>
        val adj = Array.fill(n)(List.empty[(Int, Int)])
        for
          Array(u, v, c, d, e) <- edges
          cost = c + d * (0 max (e - 10))
        do adj(u - 1) = (v - 1, cost) :: adj(u - 1)

        val (cost, dist) = dijkstra(0, adj)
        if cost == Int.MaxValue
        then "It is not a great way.\n"
        else s"${cost} ${dist}\n"

      case _ =>
        assert(false)
