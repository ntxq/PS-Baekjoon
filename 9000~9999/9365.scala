import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*
import scala.runtime.stdLibPatches.language.experimental.clauseInterleaving

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val t = input.head.toInt

    def loop(input: List[Array[Int]], acc: List[String], idx: Int): String =
      input match
        case Array(r, c) :: Array(sx, sy) :: next =>
          val (board, rest) = next.splitAt(r)
          val result        = solveCase(r, c, sx, sy, board.toArray)
          loop(rest, s"Case #$idx: $result" :: acc, idx + 1)

        case _ => acc.reverse.mkString("\n")

    loop(input.tail.map(_.split(" ").map(_.toInt)), Nil, 1)

  def solveCase(r: Int, c: Int, sx: Int, sy: Int, board: Array[Array[Int]]): Int =
    val visited = Array.fill(r, c)(false)
    val queue   = scala.collection.mutable.Queue((sx - 1, sy - 1))
    visited(sx - 1)(sy - 1) = true

    while queue.nonEmpty do
      val (x, y) = queue.dequeue()
      for
        dx <- -1 to 1
        dy <- -1 to 1
        if dx * dy == 0 && dx + dy != 0
      do
        val nx = x + dx
        val ny = y + dy
        if 0 <= nx && nx < r && 0 <= ny && ny < c && !visited(nx)(ny) && board(nx)(ny) >= board(x)(y) then
          visited(nx)(ny) = true
          queue.enqueue((nx, ny))

    (for
      i <- List(0, r - 1)
      j <- 0 until c
      if visited(i)(j)
    yield
      visited(i)(j) = false
      1
    ).sum + (for
      i <- 0 until r
      j <- List(0, c - 1)
      if visited(i)(j)
    yield
      visited(i)(j) = false
      1
    ).sum
