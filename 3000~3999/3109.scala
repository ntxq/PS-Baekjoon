import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(r, c) = readLine.split(" ").map(_.toInt)
    val board = (0 until r).map(_ => readLine.map(_ == 'x'))
    println(Bakery(board, r, c).solve)

class Bakery(board: IndexedSeq[IndexedSeq[Boolean]], r: Int, c: Int):
  val visited = Array.ofDim[Boolean](r, c)

  private def dfs(x: Int, y: Int): Boolean =
    visited(x)(y) = true
    if y == c - 1 then true
    else
      List((x - 1, y + 1), (x, y + 1), (x + 1, y + 1))
        .filter((x, y) =>
          0 <= x && x < r && 0 <= y && y < c
            && !visited(x)(y) && !board(x)(y)
        )
        .exists((x, y) => dfs(x, y))

  def solve: Int =
    (0 until r).count(x => dfs(x, 0))
