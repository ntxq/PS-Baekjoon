import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    println(countIncreasingSeq(readInt()))

  def countIncreasingSeq(n: Int): Int =
    val MOD = 10007
    val dp = Array.fill(n + 1, 10)(0)
    for i <- 0 to 9 do dp(1)(i) = 1

    for
      i <- 2 to n
      j <- 0 to 9
    do
      dp(i)(j) =
        if j == 0 then 1
        else (dp(i)(j - 1) + dp(i - 1)(j)) % MOD

    dp(n).foldLeft(0)((acc, x) => (acc + x) % MOD)
