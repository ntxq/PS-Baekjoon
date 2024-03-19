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
    val nums       = input.tail.map(_.toInt).toArray
    val sortedNums = nums.sorted
    val inserted   = Array.fill(nums.length)(false)

    (for i <- 0 until nums.length
    yield
      val j = sortedNums.search(nums(i)).insertionPoint
      inserted(j) = true

      if j == 0 && !inserted(j + 1)
      then 1
      else if j == nums.length - 1 && !inserted(j - 1)
      then 1
      else if !inserted(j - 1) && !inserted(j + 1)
      then 1
      else 0
    ).sum.toString
