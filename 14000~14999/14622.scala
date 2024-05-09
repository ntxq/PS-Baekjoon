import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

import scala.collection.mutable.PriorityQueue
object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def computeScore(
      x: Int,
      pqMe: PriorityQueue[Int],
      pqOther: PriorityQueue[Int],
      sieve: Array[Boolean],
      visited: Array[Boolean]
  ): (Long, Long) =
    (sieve(x), visited(x)) match
      case (true, true) =>
        (-1000, 0)
      case (true, false) =>
        pqMe.enqueue(x)
        visited(x) = true
        (0, 0)
      case (false, true) =>
        assert(false)
      case (false, false) =>
        if pqOther.size < 3
        then (0, 1000)
        else
          val a = pqOther.dequeue()
          val b = pqOther.dequeue()
          val c = pqOther.dequeue()
          pqOther.enqueue(a)
          pqOther.enqueue(b)
          pqOther.enqueue(c)
          (0, c)

  def solve(input: List[String]): String =
    val sieve = Array.fill(5000001)(true)
    sieve(0) = false
    sieve(1) = false
    for
      i <- 2 to 5000000
      if sieve(i)
      j <- i.toLong * i to 5000000 by i
    do sieve(j.toInt) = false

    val pqX     = PriorityQueue.empty[Int]
    val pqY     = PriorityQueue.empty[Int]
    val visited = Array.fill(5000001)(false)

    def loop(inputs: List[(Int, Int)], x: Long, y: Long): String =
      inputs match
        case Nil =>
          if x > y then "소수의 신 갓대웅\n"
          else if x < y then "소수 마스터 갓규성\n"
          else "우열을 가릴 수 없음\n"
        case (a, b) :: tail =>
          val (scoreAX, scoreAY) = computeScore(a, pqX, pqY, sieve, visited)
          val (scoreBY, scoreBX) = computeScore(b, pqY, pqX, sieve, visited)
          loop(tail, x + scoreAX + scoreBX, y + scoreAY + scoreBY)

    loop(input.tail.map(_.split(" ").map(_.toInt)).map { case Array(a, b) => (a, b) }, 0, 0)
