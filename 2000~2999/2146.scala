import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    import collection.immutable.ArraySeq

    Array
      .fill(readInt())(readLine().split(' ').map(_ == "1"))
      .map(ArraySeq.unsafeWrapArray(_))
      .pipe(ArraySeq.unsafeWrapArray(_))
      .pipe(findBridge)
      .pipe(println)

  def bfs(
      sx: Int,
      sy: Int,
      island: Int,
      board: IndexedSeq[IndexedSeq[Boolean]],
      islandVisit: Array[Array[Int]]
  ): Int =
    val waterVisit = Array.ofDim[Boolean](board.size, board.size)
    val q = collection.mutable.Queue[(Int, Int, Int)]()

    val islandQ = collection.mutable.Queue[(Int, Int)]((sx, sy))
    islandVisit(sx)(sy) = island

    while islandQ.nonEmpty do
      val (x, y) = islandQ.dequeue()

      q.enqueue((x, y, 0))
      waterVisit(x)(y) = true

      for
        (nx, ny) <- List((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
        if 0 <= nx && nx < board.size && 0 <= ny && ny < board.size
          && board(nx)(ny) && islandVisit(nx)(ny) == 0
      do
        islandVisit(nx)(ny) = island
        islandQ.enqueue((nx, ny))

    var minD = Int.MaxValue
    while minD == Int.MaxValue do
      val (x, y, d) = q.dequeue()

      for
        (nx, ny) <- List((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
        if 0 <= nx && nx < board.size && 0 <= ny && ny < board.size
          && !waterVisit(nx)(ny)
      do
        if board(nx)(ny) then minD = d
        else
          waterVisit(nx)(ny) = true
          q.enqueue((nx, ny, d + 1))

    minD

  def findBridge(board: IndexedSeq[IndexedSeq[Boolean]]): Int =
    val islandVisit = Array.ofDim[Int](board.size, board.size)

    var islandCount = 0
    var minD = Int.MaxValue
    for
      x <- board.indices
      y <- board.indices
      if board(x)(y) && islandVisit(x)(y) == 0
    do
      islandCount += 1
      minD = minD min bfs(x, y, islandCount, board, islandVisit)

    minD
