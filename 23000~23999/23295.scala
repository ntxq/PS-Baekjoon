import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val Array(_, t) = input.head.split(" ").map(_.toInt)

    val timeslots = Array.fill(100001)(0)
    for
      schedule <- input.tail
      times = schedule.split(" ").map(_.toInt)
      if times.length == 2
      Array(s, t) = times
    do
      timeslots(s) += 1
      timeslots(t) -= 1

    val prefixSum = timeslots.scanLeft(0)(_ + _)
    def loop(i: Int, curSum: Int, maxSum: Int, time: (Int, Int)): (Int, Int) =
      if i == prefixSum.length then time
      else
        val newSum  = curSum + prefixSum(i) - prefixSum(i - t)
        val newTime = if newSum > maxSum then (i - t, i) else time
        loop(i + 1, newSum, maxSum max newSum, newTime)

    val (from, to) = loop(t, prefixSum.take(t).sum, prefixSum.take(t).sum, (0, t - 1))
    s"$from $to"

