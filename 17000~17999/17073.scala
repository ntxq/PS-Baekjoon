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
    val Array(n, w) = input.head.split(" ").map(_.toInt)
    val adj         = Array.fill(n + 1)(List.empty[Int])
    for Array(u, v) <- input.tail.map(_.split(" ").map(_.toInt))
    do
      adj(u) ::= v
      adj(v) ::= u

    val q      = collection.mutable.Queue.empty[Int]
    val waters = Array.fill(n + 1)(-1.0)

    q.enqueue(1)
    waters(1) = w

    while !(q.isEmpty) do
      val u = q.dequeue()
      val w = waters(u)

      val cnt = adj(u).count(v => waters(v) < 0)

      if cnt > 0
      then
        for
          v <- adj(u)
          if waters(v) < 0
        yield
          q.enqueue(v)
          waters(v) = w / cnt
        waters(u) = 0

    val cnt = waters.count(_ > 0)
    (waters.filter(_ > 0).sum / cnt).toString
