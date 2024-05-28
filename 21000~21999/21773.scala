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
      case Array(t, n) :: tasks =>
        val pq = PriorityQueue.empty(using
          Ordering.fromLessThan[Tuple3[Int, Int, Int]] { case ((x1, y1, _), (x2, y2, _)) =>
            if x1 == x2
            then y2 < y1
            else x1 < x2
          }
        )

        for Array(id, time, priority) <- tasks
        do pq.addOne((priority, id, time))

        def loop(remainingTime: Int, acc: List[Int]): String =
          if pq.isEmpty || remainingTime == 0
          then acc.reverse.mkString("\n")
          else
            val (priority, id, time) = pq.dequeue()
            if time == 1
            then loop(remainingTime - 1, id :: acc)
            else
              pq.enqueue((priority - 1, id, time - 1))
              loop(remainingTime - 1, id :: acc)

        loop(t, Nil)

      case _ =>
        assert(false)
