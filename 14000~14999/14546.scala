import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.drop(1).toList
    val output = prisonBreak(input).mkString("\n")
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def bfs(board: Array[Array[Char]], sx: Int, sy: Int, tx: Int, ty: Int): Boolean =
    val visited = Array.fill(board.length, board(0).length)(false)
    val queue   = scala.collection.mutable.Queue.empty[(Int, Int)]

    visited(sx)(sy) = true
    queue.enqueue((sx, sy))

    while queue.nonEmpty && !visited(tx)(ty) do
      val (x, y) = queue.dequeue()
      for
        (dx, dy) <- List((1, 0), (-1, 0), (0, 1), (0, -1))
        nx = x + dx
        ny = y + dy
        if 0 <= nx && nx < board.length && 0 <= ny && ny < board(0).length
        if !visited(nx)(ny) && board(nx)(ny) == board(x)(y)
      do
        visited(nx)(ny) = true
        queue.enqueue((nx, ny))

    visited(tx)(ty)

  def prisonBreak(input: List[String]): List[String] =
    def loop(input: List[String], acc: List[String]): List[String] =
      input match
        case Nil => acc.reverse
        case dims :: rest =>
          val Array(l, w, sy, sx, ty, tx) = dims.split(" ").map(_.toInt)
          val board                       = rest.take(w).reverse.map(_.toCharArray).toArray

          val result = if bfs(board, sx - 1, sy - 1, tx - 1, ty - 1) then "YES" else "NO"
          loop(rest.drop(w), result :: acc)

    loop(input, Nil)
