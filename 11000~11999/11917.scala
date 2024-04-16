import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toArray
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: Array[String]): String =
    input.map(_.split(" ").map(_.toInt)) match
      case Array(Array(n), nums, Array(m)) =>
        if m <= n
        then nums(m - 1).toString
        else
          val sortedNums = nums.sorted
          val initCnt    = sortedNums.distinct.size
          val limit      = sortedNums(sortedNums.search(initCnt).insertionPoint)

          (limit min (m - n - 1 + initCnt)).toString

      case _ =>
        assert(false)
