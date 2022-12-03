import io.StdIn.*
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    readInt().pipe(countTiles).pipe(println)

  def countTiles(size: Int): Int =
    val dp = Array.fill(31)(0)
    dp(0) = 1
    dp(2) = 3

    for i <- 4 to size by 2
    do
      dp(i) = dp(i - 2) * 3
      for j <- 4 to i by 2
      do dp(i) += dp(i - j) * 2
    dp(size)
