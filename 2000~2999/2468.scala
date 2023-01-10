import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val size = readInt()
    val board =
      for _ <- 0 until size
      yield readLine().split(" ").map(_.toInt)

    println(countSafePlaces(size, board.toArray))

  def countSafePlaces(size: Int, board: Array[Array[Int]]): Int =
    def tryRain(depth: Int): Int =
      val visited = Array.ofDim[Boolean](size, size)

      def bfs(sx: Int, sy: Int): Unit =
        val queue = collection.mutable.Queue((sx, sy))
        visited(sx)(sy) = true

        while queue.nonEmpty do
          val (ux, uy) = queue.dequeue()
          for
            (dx, dy) <- (0, 1) :: (0, -1) :: (1, 0) :: (-1, 0) :: Nil
            vx = ux + dx
            vy = uy + dy
            if 0 <= vx && vx < size && 0 <= vy && vy < size && board(vx)(
              vy
            ) > depth && !visited(vx)(vy)
          do
            queue.enqueue((vx, vy))
            visited(vx)(vy) = true

      var count = 0
      for
        x <- 0 until size
        y <- 0 until size
        if board(x)(y) > depth && !visited(x)(y)
      do
        count += 1
        bfs(x, y)

      count

    (0 to 100).map(tryRain).max
