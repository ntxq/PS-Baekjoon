import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, k) = readLine.split(' ').map(_.toInt)
    val board =
      for _ <- 0 until 2
      yield readLine().toCharArray()

    println(bfs(n, k, board))

  def bfs(n: Int, k: Int, board: IndexedSeq[Array[Char]]): Int =
    val visited = Array.fill(2, n)(false)

    def next(time: Int)(x: Int, y: Int): List[(Int, Int)] =
      for
        (nx, ny) <- List((x, y + 1), (x, y - 1), (1 - x, y + k))
        if time < ny && (ny >= n || (!visited(nx)(ny) && board(nx)(ny) == '1'))
      yield
        if ny < n then visited(nx)(ny) = true
        (nx, ny)

    @tailrec
    def loop(xs: List[(Int, Int)], time: Int): Int =
      if xs.exists((_, y) => y >= n) then 1
      else if xs.nonEmpty then
        val ys = xs.flatMap(next(time).tupled)
        loop(ys, time + 1)
      else 0

    loop(List((0, 0)), 0)
