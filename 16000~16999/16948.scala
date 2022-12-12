import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val board = readInt()
    val Array(fromX, fromY, toX, toY) = readLine().split(" ").map(_.toInt)
    println(DeathKnight((fromX, fromY), (toX, toY), board).solve)

class DeathKnight(from: (Int, Int), to: (Int, Int), board: Int):
  private val moves =
    Vector((-2, -1), (-2, 1), (0, -2), (0, 2), (2, -1), (2, 1))
  private def next(from: (Int, Int)) =
    moves
      .map((dx, dy) => (from._1 + dx, from._2 + dy))
      .filter((x, y) => 0 <= x && x < board && 0 <= y && y < board)

  @tailrec
  private def bfs(
      from: Set[(Int, Int)],
      visited: Array[Array[Boolean]],
      dist: Int
  ): Int =
    if from.isEmpty then -1
    else if from.contains(to) then dist
    else
      val nexts = from.flatMap(next).filter((x, y) => !visited(x)(y))
      nexts.foreach((x, y) => visited(x)(y) = true)
      bfs(nexts, visited, dist + 1)

  def solve: Int =
    bfs(Set(from), Array.fill(board, board)(false), 0)
