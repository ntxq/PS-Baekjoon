import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine.split(' ').map(_.toInt)

    val dp = Array.fill(n, m)(Int.MaxValue)
    dp(0)(0) = 0

    for
      i <- 0 until n
      j <- 0 until m
    do
      for
        k <- 0 until i
      do
        dp(i)(j) = dp(i)(j) min (dp(k)(j) + dp(i - k - 1)(j) + 1)

      for
        k <- 0 until j
      do
        dp(i)(j) = dp(i)(j) min (dp(i)(k) + dp(i)(j - k - 1) + 1)  

    println(dp(n - 1)(m - 1))
