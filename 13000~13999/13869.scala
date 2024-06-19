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
    val n      = input.head.toInt
    val scores = input.tail.flatMap(_.split(" ").map(_.toInt)).sorted(using Ordering[Int].reverse)

    val order = collection.mutable.ArrayDeque.empty[Int]
    for (score, idx) <- scores.zipWithIndex
    do
      if idx % 2 == 0
      then order.prepend(score)
      else order.append(score)

    def loop(idx: Int, acc: Double, lastX: Double, lastY: Double): Double =
      if idx > n
      then acc * 0.5
      else
        val angle = (idx % n) * (2 * math.Pi / n)
        val curX  = math.cos(angle) * order(idx % n)
        val curY  = math.sin(angle) * order(idx % n)

        loop(
          idx + 1,
          if idx > 0
          then acc + lastX * curY - lastY * curX
          else acc,
          curX,
          curY
        )

    "%.3f".format(loop(0, 0, -1, -1))
