import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    var w = -1
    var h = -1
    while
      readLine().split(' ').map(_.toInt).pipe { case Array(x, y) =>
        w = x; h = y
      }
      w != 0 && h != 0
    do
      Array
        .fill(h)(readLine().split(' ').map(_.toInt))
        .pipe(countIslands)
        .pipe(println)

  def countIslands(board: Array[Array[Int]]): Int =
    def visit(i: Int, j: Int, idx: Int): Unit =
      if 0 <= i
        && i < board.length
        && 0 <= j
        && j < board(i).length
        && board(i)(j) == 1
      then
        board(i)(j) = idx

        for
          dx <- -1 to 1
          dy <- -1 to 1
        do visit(i + dx, j + dy, idx)

    var count = 2;
    for
      i <- board.indices
      j <- board(i).indices
      if board(i)(j) == 1
    do
      visit(i, j, count)
      count += 1

    count - 2
