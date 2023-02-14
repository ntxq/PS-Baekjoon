import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m, p) = readLine().split(' ').map(_.toInt)
    val steps = readLine().split(' ').map(_.toInt)
    val board =
      for _ <- (0 until n).toArray
      yield readLine().toCharArray().map {
        case '.' => 0
        case '#' => -1
        case c   => c - '0'
      }

    bfs(steps, board, n, m).mkString(" ").pipe(println)

  final def bfs(
      steps: Array[Int],
      board: Array[Array[Int]],
      n: Int,
      m: Int
  ): Array[Int] =
    val queues = Array.fill(steps.length)(Nil: List[(Int, Int)])
    val sizes = Array.fill(steps.length)(0)

    for
      x <- 0 until n
      y <- 0 until m
      if board(x)(y) > 0
    do
      val player = board(x)(y) - 1
      queues(player) = (x, y) :: queues(player)
      sizes(player) += 1

    def isSafe(x: Int, y: Int) =
      0 <= x && x < n && 0 <= y && y < m && board(x)(y) == 0
    def next(x: Int, y: Int) =
      (x + 1, y) :: (x - 1, y) :: (x, y + 1) :: (x, y - 1) :: Nil
    def expand(player: Int): Boolean =
      queues(player) = for
        (x, y) <- queues(player)
        (nx, ny) <- next(x, y)
        if isSafe(nx, ny)
      yield
        board(nx)(ny) = player + 1
        sizes(player) += 1
        (nx, ny)
      !queues(player).isEmpty

    while !queues.forall(_.isEmpty) do
      for (step, player) <- steps.zipWithIndex
      do
        LazyList
          .range(0, step)
          .map(_ => expand(player))
          .takeWhile(identity)
          .force

    sizes
