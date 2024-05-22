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

  def solve(input: List[String]): String =
    input match
      case dims :: key :: boardList =>
        val Array(w, h) = dims.split(" ").map(_.toInt)
        val board       = boardList.reverse.map(_.toCharArray.map(_.asDigit)).toArray

        val dp = Array.fill(key.length + 1, h, w)(Int.MaxValue)
        dp(0)(0)(0) = board(0)(0)

        for
          k <- 0 to key.length
          i <- 0 until h
          j <- 0 until w
        do
          if i > 0 && dp(k)(i - 1)(j) != Int.MaxValue
          then dp(k)(i)(j) = dp(k)(i)(j) min (dp(k)(i - 1)(j) + board(i)(j))

          if j > 0 && dp(k)(i)(j - 1) != Int.MaxValue
          then dp(k)(i)(j) = dp(k)(i)(j) min (dp(k)(i)(j - 1) + board(i)(j))

          if k > 0
          then
            val hop = key(k - 1).asDigit + 1

            if i - hop >= 0 && dp(k - 1)(i - hop)(j) != Int.MaxValue
            then dp(k)(i)(j) = dp(k)(i)(j) min (dp(k - 1)(i - hop)(j) + board(i)(j))

            if j - hop >= 0 && dp(k - 1)(i)(j - hop) != Int.MaxValue
            then dp(k)(i)(j) = dp(k)(i)(j) min (dp(k - 1)(i)(j - hop) + board(i)(j))

        (0 to key.length).map(dp(_)(h - 1)(w - 1)).min.toString

      case _ =>
        assert(false)
