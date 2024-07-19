import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def getPrefix(s: Array[String]): Array[Int] =
    val n  = s.length
    val pi = Array.fill(n)(0)

    for i <- 1 until n
    do
      def loop(j: Int): Int =
        if j > 0 && s(i) != s(j)
        then loop(pi(j - 1))
        else if s(i) == s(j)
        then j + 1
        else j
      pi(i) = loop(pi(i - 1))

    pi

  def solve(input: List[String]): String =
    val n      = input(0).toInt
    val nums   = input(1).split(" ").reverse
    val prefix = getPrefix(nums)

    (for i <- 0 until n
    yield
      val k = n - i - 1
      val p = i + 1 - prefix(i)
      (k, p)
    ).min(Ordering.fromLessThan { case ((k1, p1), (k2, p2)) =>
      val sum1 = k1 + p1
      val sum2 = k2 + p2
      if sum1 != sum2 then sum1 < sum2
      else p1 < p2
    }) match
      case (k, p) => s"$k $p"
