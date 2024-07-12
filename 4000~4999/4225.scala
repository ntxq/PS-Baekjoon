import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

case class Point(x: Int, y: Int)

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    def loop(input: List[String], acc: List[String]): List[String] =
      input match
        case List("0") | Nil => acc.reverse
        case x :: xs =>
          val n          = x.toInt
          val (ns, rest) = xs.splitAt(n)
          loop(rest, handleCase(ns) :: acc)

    (for (i, x) <- loop(input, Nil).zipWithIndex
    yield s"Case ${x + 1}: $i").mkString("\n")

  def orientation(a: Point, b: Point, c: Point): Int =
    val v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

    if v < 0 then -1      // clockwise
    else if v > 0 then +1 // counter-clockwise
    else 0

  def distance(target: Point, p0: Point, p1: Point): Double =
    val dx = (p1.x - p0.x)
    val dy = (p1.y - p0.y)

    val num = (dy * target.x - dx * target.y + p0.y * p1.x - p0.x * p1.y).abs
    val den = Math.sqrt(dx * dx + dy * dy)
    num / den

  def handleCase(input: List[String]): String =
    val points = input.map(_.split(" ").map(_.toInt)).map { case Array(x, y) => Point(x, y) }

    val p0 = points.minBy(pt => (pt.y, pt.x))
    val sorted = points.sortWith((a, b) =>
      val o = orientation(p0, a, b)
      if o == 0 then
        val d1 = (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y)
        val d2 = (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y)
        d1 < d2
      else o < 0
    )

    val stack = collection.mutable.Stack.empty[Point]
    for p <- sorted
    do
      while stack.size > 1 && orientation(stack(1), stack.top, p) >= 0
      do stack.pop()

      stack.push(p)

    val dist = (for
      i <- 0 until stack.size
      j = (i + 1) % stack.size
    yield (for
      k <- 0 until stack.size
      if k != i && k != j
    yield distance(stack(k), stack(i), stack(j))).max).min
    
    val distF = (dist * 100).ceil / 100
    f"$distF%.2f"
    
