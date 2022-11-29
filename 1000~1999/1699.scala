import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    println(squareSum(readInt()))

  def squareSum(target: Int): Int =
    val dp = Array.fill(target + 1)(Int.MaxValue)
    dp(0) = 0
    for
      i <- 1 to target
      j <- 1 to Math.sqrt(i).toInt
    do dp(i) = dp(i) min (dp(i - j * j) + 1)

    dp(target)
