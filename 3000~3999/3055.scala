import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(r, c) = readLine().split(' ').map(_.toInt)
    val board = Array.fill(r)(readLine().toCharArray)

    val flood = calcFlood(board)

    bfs(board, flood) match
      case Some(ans) => println(ans)
      case None      => println("KAKTUS")

  final def calcFlood(board: Array[Array[Char]]): Array[Array[Int]] =
    val dist = Array.fill(board.length, board(0).length)(Int.MaxValue)
    val queue = collection.mutable.Queue[(Int, Int)]()

    for
      i <- board.indices
      j <- board(0).indices
      if board(i)(j) == '*'
    do
      dist(i)(j) = 0
      queue.enqueue((i, j))

    while queue.nonEmpty do
      val (x, y) = queue.dequeue()

      for
        (nx, ny) <- List((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
        if 0 <= nx && nx < board.length && 0 <= ny && ny < board(0).length
          && dist(x)(y) + 1 < dist(nx)(ny)
          && board(nx)(ny) != 'X' && board(nx)(ny) != 'D'
      do
        dist(nx)(ny) = dist(x)(y) + 1
        queue.enqueue((nx, ny))

    dist

  final def bfs(
      board: Array[Array[Char]],
      flood: Array[Array[Int]]
  ): Option[Int] =
    val dist = Array.fill(board.length, board(0).length)(Int.MaxValue)
    val queue = collection.mutable.Queue[(Int, Int)]()

    for
      i <- board.indices
      j <- board(0).indices
      if board(i)(j) == 'S'
    do
      dist(i)(j) = 0
      queue.enqueue((i, j))

    while queue.nonEmpty do
      val (x, y) = queue.dequeue()

      for
        (nx, ny) <- List((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
        if 0 <= nx && nx < board.length && 0 <= ny && ny < board(0).length
          && dist(x)(y) + 1 < dist(nx)(ny)
          && board(nx)(ny) != 'X' && dist(x)(y) + 1 < flood(nx)(ny)
      do
        dist(nx)(ny) = dist(x)(y) + 1
        queue.enqueue((nx, ny))

    (for
      i <- board.indices
      j <- board(0).indices
      if board(i)(j) == 'D' && dist(i)(j) != Int.MaxValue
    yield
      dist(i)(j)).headOption
