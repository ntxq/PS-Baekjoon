import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def gcd(a: Int, b: Int): Int =
    if b > a
    then gcd(b, a)
    else if b == 0
    then 0
    else if a / b == 1
    then 1 - gcd(b, a % b)
    else 1

  def solve(input: List[String]): String =
    (for
      Array(a, b) <- input.map(_.split(" ").map(_.toInt))
      if a != 0 && b != 0
    yield gcd(a, b) % 2 match
      case 0 => "B wins"
      case _ => "A wins"
    ).mkString("\n")
