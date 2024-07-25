import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def binaryPower(a: Long, b: Long, m: Long): Long =
    def loop(a: Long, b: Long, res: Long): Long =
      if b <= 0
      then res
      else if b % 2 == 0
      then loop((a * a) % m, b / 2, res)
      else loop((a * a) % m, b / 2, (res * a) % m)
    loop(a % m, b, 1)

  def solve(input: List[String]): String =
    (((for Array(c, k) <- input.tail.map(_.split("[ \t]").map(_.toLong))
    yield
      val a = (c * k) % 1_000_000_007L
      (a * binaryPower(2, k - 1, 1_000_000_007L)) % 1_000_000_007L
    ).sum) % 1_000_000_007L).toString
