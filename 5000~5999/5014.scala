import io.StdIn.*
import collection.mutable.{ArrayBuffer, Queue}

object Main:
  def main(args: Array[String]): Unit =
    readLine().split(" ").map(_.toInt) match
      case Array(f, s, g, u, d) =>
        val elevator = Elevator(f, s, g, u, d)
        val dist = elevator.bfs
        println(if dist == -1 then "use the stairs" else dist)

class Elevator(f: Int, s: Int, g: Int, u: Int, d: Int):
  def bfs: Int =
    val q = Queue(s - 1)
    val dist = Array.ofDim[Int](f)

    dist(s - 1) = 1

    while q.nonEmpty && dist(g - 1) == 0 do
      val cur = q.dequeue
      val next = Array(cur + u, cur - d).filter(x => x >= 0 && x < f)

      for n <- next do
        if dist(n) == 0 then
          dist(n) = dist(cur) + 1
          q.enqueue(n)

    if dist(g - 1) == 0 then -1 else dist(g - 1) - 1
