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
    val pq = scala.collection.mutable.PriorityQueue.empty[Int].reverse
    def loop(maxCount: Int, todos: List[(Int, Int)]): Int =
      todos match
        case Nil => maxCount
        case (start, end) :: rest =>
          while pq.nonEmpty && pq.head <= start do pq.dequeue
          pq.enqueue(end)
          loop(pq.size max maxCount, rest)

    loop(0, input.tail.map(_.split(" ").map(_.toInt)).map { case Array(s, t) => (s, t) }.sorted).toString
