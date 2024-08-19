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
    def loop(input: List[String], acc: List[String]): String =
      input match
        case "*" :: xs =>
          val (triangles, rest) = xs.splitAt(6)
          val caseInput = triangles
            .map(_.split(" ").map(_.toInt) match
              case Array(a, b, c) => (a, b, c)
            )
            .toArray
          loop(rest, solveCase(caseInput) :: acc)
        case _ => acc.reverse.mkString("\n")

    loop("*" :: input, Nil)

  def solveCase(triangles: Array[(Int, Int, Int)]): String =
    val isUsed = Array.fill(6)(false)

    def loop(idx: Int, prev: Int, last: Int, acc: Int): Int =
      if idx == 5
      then
        val (a, b, c) = triangles(isUsed.indexOf(false))
        if a == last && b == prev
        then acc + c
        else if b == last && c == prev
        then acc + a
        else if c == last && a == prev
        then acc + b
        else 0
      else
        (for
          i <- 0 until 6
          if !isUsed(i)
          (a, b, c) = triangles(i)
        yield
          isUsed(i) = true
          val res =
            (if a == prev then loop(idx + 1, c, last, acc + b) else 0) max
              (if b == prev then loop(idx + 1, a, last, acc + c) else 0) max
              (if c == prev then loop(idx + 1, b, last, acc + a) else 0)
          isUsed(i) = false
          res
        ).max

    (for
      i <- 0 until 6
      (a, b, c) = triangles(i)
    yield
      isUsed(i) = true
      val res = loop(1, a, b, c) max loop(1, b, c, a) max loop(1, c, a, b)
      isUsed(i) = false
      res
    ).max match
      case 0 => "none"
      case x => x.toString
