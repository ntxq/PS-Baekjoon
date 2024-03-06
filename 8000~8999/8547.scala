import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*
import scalajs.js.BigInt

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    input match
      case _ :: sticks :: Nil =>
        val pq = scala.collection.mutable.PriorityQueue.from(sticks.split(" ").map(_.toInt))(using Ordering.Int.reverse)

        def loop(prev: Int, cnt: Int): Int =
          pq.headOption match
            case Some(cur) =>
              if cur == prev
              then
                pq.enqueue(prev + pq.dequeue())
                loop(pq.dequeue(), cnt)
              else loop(pq.dequeue(), cnt + 1)
            case None =>
              cnt + 1

        loop(pq.dequeue(), 0).toString

      case _ =>
        assert(false)
