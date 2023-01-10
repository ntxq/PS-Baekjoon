import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(m, n, k) = readLine().split(" ").map(_.toInt)
    val board = Array.ofDim[Boolean](n, m)

    for
      _ <- 0 until k
      Array(sx, sy, tx, ty) = readLine().split(" ").map(_.toInt)
      x <- sx until tx
      y <- sy until ty
    do board(x)(y) = true

    val areas = bfs(board)
    println(areas.size)
    println(areas.mkString(" "))

  def bfs(board: Array[Array[Boolean]]): Vector[Int] =
    val vb = Vector.newBuilder[Int]
    val visited = Array.ofDim[Boolean](board.length, board(0).length)
    val queue = collection.mutable.Queue[(Int, Int)]()

    for
      sx <- 0 until board.length
      sy <- 0 until board(0).length
      if !visited(sx)(sy) && !board(sx)(sy)
    do
      var area = 1
      queue.enqueue((sx, sy))
      visited(sx)(sy) = true

      while queue.nonEmpty do
        val (ux, uy) = queue.dequeue()

        for
          (dx, dy) <- List((0, 1), (0, -1), (1, 0), (-1, 0))
          (vx, vy) = (ux + dx, uy + dy)
          if 0 <= vx && vx < board.length &&
            0 <= vy && vy < board(0).length &&
            !visited(vx)(vy) && !board(vx)(vy)
        do
          queue.enqueue((vx, vy))
          area += 1
          visited(vx)(vy) = true

      vb += area

    vb.result().sorted
