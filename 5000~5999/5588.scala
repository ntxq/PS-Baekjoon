import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val m = input.head.toInt
    val (targets, rest) =
      val (targets, rest) = input.tail.map(_.split(" ").map(_.toInt)).splitAt(m)
      (targets.map { case Array(x, y) => (x, y) }, rest)

    val n     = rest.head.head
    val stars = rest.tail.map { case Array(x, y) => (x, y) }.toSet

    (for
      (sx, sy) <- stars
      (tx, ty) = targets.head
      dx       = sx - tx
      dy       = sy - ty
      if targets.forall((x, y) => stars.contains((x + dx, y + dy)))
    yield s"$dx $dy").head
