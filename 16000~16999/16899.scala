import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = quarryGame(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def f(n: Long): Long =
    (n % 4) match
      case 0 => n
      case 1 => 1
      case 2 => n + 1
      case 3 => 0

  def g(n: Long, m: Long): Long =
    f(n - 1) ^ f(m)

  def quarryGame(input: List[String]): String =
    if input.tail.map(_.split(" ").map(_.toLong)).foldLeft(0L) { case (acc, Array(x, m)) =>
        acc ^ g(x, x + m - 1)
      } > 0
    then "koosaga"
    else "cubelover"
