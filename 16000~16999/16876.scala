import typings.node.{fsMod as fs}

import scala.scalajs.js.Math
import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList.head
    val output = numberGame(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def candidates(n: List[Int]): List[List[Int]] =
    for i <- (0 until 4).toList
    yield n.updated(i, (n(i) + 1) % 10)

  def numToList(n: Int): List[Int] =
    def loop(x: Int, acc: List[Int]): List[Int] =
      if x == 0 then acc else loop(x / 10, x % 10 :: acc)

    val res = loop(n, Nil)
    if res.length < 4 then List.fill(4 - res.length)(0) ++ res else res

  def numberGame(input: String): String =
    val dp = Array.fill(101, 10000)(-1)
    def loop(num: List[Int], turn: Int, n: Int, m: Int): Boolean =
      val sum = num.foldLeft(0)((acc, x) => acc * 10 + x)
      if turn == m
      then
        if m % 2 == 1
        then sum <= n
        else sum > n
      else if dp(turn)(sum) != -1
      then dp(turn)(sum) == 1
      else
        val playerWins =
          if candidates(num).forall(loop(_, turn + 1, n, m))
          then 0
          else 1
        dp(turn)(sum) = playerWins
        playerWins == 1

    val Array(n, m) = input.split(" ").map(_.toInt)
    if loop(numToList(n), 0, n, m) then "koosaga" else "cubelover"
