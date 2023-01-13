import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

case class Panda(board: IndexedSeq[IndexedSeq[Int]]):
  val dp = Array.ofDim[Int](board.length, board(0).length)

  private def dfs(x: Int, y: Int): Int =
    if dp(x)(y) > 0 then dp(x)(y)
    else
      dp(x)(y) = 1
      for
        (nx, ny) <- List((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
        if 0 <= nx && nx < board.length && 0 <= ny && ny < board(0).length
          && board(x)(y) < board(nx)(ny)
      do dp(x)(y) = dp(x)(y) max (dfs(nx, ny) + 1)

      dp(x)(y)

  def solve: Int =
    val max = (for
      x <- board.indices
      y <- board(0).indices
    yield dfs(x, y)).max

    max

object Main:
  def main(args: Array[String]): Unit =
    import scala.collection.immutable.ArraySeq

    val n = readInt()
    Array
      .fill(n)(readLine().split(' ').map(_.toInt))
      .map(ArraySeq.unsafeWrapArray(_))
      .pipe(ArraySeq.unsafeWrapArray(_))
      .pipe(Panda(_))
      .pipe(_.solve)
      .pipe(println)
