import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

enum Piece:
  case Knight
  case Bishop
  case Rook

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val board =
      for _ <- (0 until n).toArray
      yield readLine().split(' ').map(_.toInt)

    bfs(n, board) pipe ((d, s) => println(s"$d $s"))

  final def bfs(n: Int, board: Array[Array[Int]]): (Int, Int) =
    import collection.mutable.Queue
    val q = Queue.empty[(Int, Int, Int, Piece)]
    val dist = Array.fill(n, n, n * n + 1, Piece.values.size)(
      (Int.MaxValue, Int.MaxValue)
    )

    for
      x <- 0 until n
      y <- 0 until n
      if board(x)(y) == 1
      shape <- Piece.values
    do
      dist(x)(y)(0)(shape.ordinal) = (0, 0)
      q += ((x, y, 0, shape))

    import math.Ordering.Implicits.*
    while !q.isEmpty do
      val (x, y, target, shape) = q.dequeue()
      val curDist = dist(x)(y)(target)(shape.ordinal)

      if board(x)(y) == target + 1
        && curDist < dist(x)(y)(target + 1)(shape.ordinal)
      then
        dist(x)(y)(target + 1)(shape.ordinal) = curDist
        q += ((x, y, target + 1, shape))

      for
        nShape <- Piece.values
        nDist = (curDist._1 + 1, curDist._2 + 1)
        if shape != nShape
        if nDist < dist(x)(y)(target)(nShape.ordinal)
      do
        dist(x)(y)(target)(nShape.ordinal) = nDist
        q += ((x, y, target, nShape))

      import Piece.*
      val nDist = (curDist._1 + 1, curDist._2)
      shape match
        case Knight =>
          for
            (nx, ny) <- List(
              (x + 2, y + 1),
              (x + 2, y - 1),
              (x - 2, y + 1),
              (x - 2, y - 1),
              (x + 1, y + 2),
              (x + 1, y - 2),
              (x - 1, y + 2),
              (x - 1, y - 2)
            )
            if 0 <= nx && nx < n && 0 <= ny && ny < n
            if nDist < dist(nx)(ny)(target)(shape.ordinal)
          do
            dist(nx)(ny)(target)(shape.ordinal) = nDist
            q += ((nx, ny, target, shape))

        case Bishop =>
          for
            i <- 0 until n
            (dx, dy) <- List((1, 1), (1, -1), (-1, 1), (-1, -1))
            (nx, ny) = (x + dx * i, y + dy * i)
            if 0 <= nx && nx < n && 0 <= ny && ny < n
            if nDist < dist(nx)(ny)(target)(shape.ordinal)
          do
            dist(nx)(ny)(target)(shape.ordinal) = nDist
            q += ((nx, ny, target, shape))

        case Rook =>
          for
            i <- 0 until n
            (dx, dy) <- List((1, 0), (-1, 0), (0, 1), (0, -1))
            (nx, ny) = (x + dx * i, y + dy * i)
            if 0 <= nx && nx < n && 0 <= ny && ny < n
            if nDist < dist(nx)(ny)(target)(shape.ordinal)
          do
            dist(nx)(ny)(target)(shape.ordinal) = nDist
            q += ((nx, ny, target, shape))

    (for
      x <- 0 until n
      y <- 0 until n
      if board(x)(y) == n * n
      shape <- Piece.values.indices
    yield dist(x)(y)(n * n)(shape)).min
