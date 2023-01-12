import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine().split(' ').map(_.toInt)
    val board = Array.fill(n)(readLine().split(' ').map(_.toInt))

    countYears(board).pipe(println)

  def countIslands(board: Array[Array[Int]]): Int =
    val visited = Array.ofDim[Boolean](board.length, board(0).length)
    val q = collection.mutable.Queue.empty[(Int, Int)]

    def bfs(sx: Int, sy: Int): Unit =
      visited(sx)(sy) = true
      q.enqueue((sx, sy))

      while q.nonEmpty do
        val (x, y) = q.dequeue()

        for
          (nx, ny) <- List((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
          if 0 <= nx && nx < board.length
            && 0 <= ny && ny < board(nx).length
            && !visited(nx)(ny) && board(nx)(ny) > 0
        do
          visited(nx)(ny) = true
          q.enqueue((nx, ny))

    var count = 0
    for
      i <- board.indices
      j <- board(i).indices
      if !visited(i)(j) && board(i)(j) > 0
    do
      bfs(i, j)
      count += 1

    count

  def updateIslands(board: Array[Array[Int]]): Array[Array[Int]] =
    val newBoard = Array.ofDim[Int](board.length, board(0).length)

    for
      i <- 1 until board.length - 1
      j <- 1 until board(i).length - 1
      if board(i)(j) != 0
    do
      newBoard(i)(j) = (board(i)(j)
        - (if board(i - 1)(j) == 0 then 1 else 0)
        - (if board(i + 1)(j) == 0 then 1 else 0)
        - (if board(i)(j - 1) == 0 then 1 else 0)
        - (if board(i)(j + 1) == 0 then 1 else 0)) max 0

    newBoard

  def countYears(board: Array[Array[Int]]) =
    lazy val years: LazyList[(Int, Array[Array[Int]])] =
      (0, board) #:: years.map((y, b) => (y + 1, updateIslands(b)))

    val (year, finalBoard) = years
      .find((y, b) =>
        val count = countIslands(b)
        count == 0 || count > 1
      )
      .get

    if countIslands(finalBoard) == 0 then 0 else year
