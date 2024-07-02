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
    val pq = collection.mutable.PriorityQueue.empty[(Int, Int)].reverse
    for
      Array(uy, um, vy, vm) <- input.tail.map(_.split(" ").flatMap(_.split("-")).map(_.toInt))
    do
      pq.enqueue((uy * 12 + um - 1, 1))
      pq.enqueue((vy * 12 + vm, -1))

    def loop(curCnt: Int, maxCnt: Int, maxTime: Int): String =
      if pq.isEmpty
      then f"${maxTime / 12}-${maxTime % 12 + 1}%02d"
      else
        val (time, diff) = pq.dequeue()
        val nextCnt      = curCnt + diff

        if nextCnt > maxCnt
        then loop(nextCnt, nextCnt, time)
        else loop(nextCnt, maxCnt, maxTime)

    loop(0, 0, 0)
