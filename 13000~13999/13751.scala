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
    val Array(b, p)    = input.head.split(" ").map(_.toInt)
    val (bars, plates) = input.tail.map(_.toInt).splitAt(b)

    val weights = collection.mutable.SortedSet.empty[Int]
    def loop(plates: List[Int], left: Int, right: Int): Unit =
      plates match
        case Nil =>
          if left == right
          then
            for bar <- bars
            do weights += (left + right + bar)

        case p :: ps =>
          loop(ps, left + p, right)
          loop(ps, left, right + p)
          loop(ps, left, right)

    loop(plates, 0, 0)
    weights.mkString("\n")
