import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps
import scala.util.Try

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine.split(" ").map(_.toInt)
    val board =
      for _ <- (0 until n).toVector
      yield readLine().toVector
    val (coin1, coin2) =
      board.zipWithIndex
        .flatMap((row, i) =>
          row.zipWithIndex.collect { case ('o', j) =>
            (i, j)
          }
        )
        .pipe(coins => (coins(0), coins(1)))
    TwoCoins(board, coin1, coin2).solve.pipe(println)

class TwoCoins(
    val board: Vector[Vector[Char]],
    val coin1: (Int, Int),
    val coin2: (Int, Int)
):
  type Position = (Int, Int)
  enum Move(val dx: Int, val dy: Int):
    case U extends Move(-1, 0)
    case D extends Move(1, 0)
    case L extends Move(0, -1)
    case R extends Move(0, 1)
    def next(pos: Position): Position =
      val nextPos = (pos._1 + dx, pos._2 + dy)
      if (isWall(nextPos)) pos else nextPos

  def isOut(pos: Position): Boolean =
    pos._1 < 0 || pos._1 >= board.size || pos._2 < 0 || pos._2 >= board(0).size

  def isWall(pos: Position): Boolean =
    Try(board(pos._1)(pos._2) == '#').getOrElse(false)

  def bfs(
      positions: List[(Position, Position)],
      dist: Int,
      visited: Set[(Position, Position)]
  ): Int =
    if dist > 10 then -1
    else if positions.exists((c1, c2) => isOut(c1) ^ isOut(c2)) then dist
    else
      Move.values.toList
        .flatMap(move =>
          positions.map((c1, c2) => (move.next(c1), move.next(c2)))
        )
        .filterNot((c1, c2) =>
          isOut(c1) && isOut(c2) ||
            visited.contains((c1, c2)) ||
            visited.contains((c2, c1))
        )
        .pipe(nextPositions =>
          bfs(nextPositions, dist + 1, visited ++ nextPositions)
        )

  def solve: Int =
    bfs(List((coin1, coin2)), 0, Set((coin1, coin2)))
