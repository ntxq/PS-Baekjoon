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
    val pq =
      collection.mutable.PriorityQueue.empty[(Int, Int, Int)](using Ordering[(Int, Int, Int)].reverse)

    for case Array(idx, s, t) <- input.drop(1).map(_.split(" ").map(_.toInt))
    do
      pq.enqueue((s, 1, idx))
      pq.enqueue((t, -1, idx))

    val rooms = collection.mutable.PriorityQueue.empty[Int](using Ordering[Int].reverse)
    def loop(count: Int, acc: Map[Int, Int]): Map[Int, Int] =
      if pq.isEmpty then acc
      else
        val (time, delta, idx) = pq.dequeue()
        if delta == -1
        then
          val newCount = count + delta
          val prevRoom = acc(idx)
          rooms.enqueue(prevRoom)
          loop(newCount, acc)
        else
          val newCount = count + delta
          val newRoom =
            if rooms.isEmpty then count + 1
            else rooms.dequeue()
          val newAcc = acc.updated(idx, newRoom)
          loop(newCount, newAcc)

    val ans = loop(0, Map.empty).toList.sortBy(_._1).map(_._2)
    ans.max.toString + "\n" + ans.mkString("\n")
