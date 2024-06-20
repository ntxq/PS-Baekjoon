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
    (for Array(s, t) <- input.tail.map(_.split(" "))
    yield
      val idx = (s.length - t.length) / 2

      if s.length == t.length
      then s == t
      else if (s.length - t.length) % 2 == 1
      then s.substring(idx).startsWith(t) && s.substring(idx + 1).startsWith(t)
      else
        s.substring(idx).startsWith(t) || (
          s.substring(idx - 1).startsWith(t) && s.substring(idx + 1).startsWith(t)
        )
    )
      .map(if _ then "Alice" else "Bob")
      .mkString("\n")
