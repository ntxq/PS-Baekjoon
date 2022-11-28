import io.StdIn.*
import scala.annotation.tailrec

object Main:
  val dp = computeDP

  def main(args: Array[String]): Unit =
    val t = readInt()
    val output =
      for _ <- 0 until t
      yield dp(readInt())
    println(output.mkString("\n"))

  def computeDP: Array[Int] =
    val limit = 100001
    val mod = 1000000009

    val dp = Array.fill(limit, 3)(0)
    dp(1)(0) = 1
    dp(2)(1) = 1
    dp(3)(0) = 1
    dp(3)(1) = 1
    dp(3)(2) = 1

    for i <- 4 until limit
    do
      dp(i)(0) = (dp(i - 1)(1) + dp(i - 1)(2)) % mod
      if i > 1 then dp(i)(1) = (dp(i - 2)(0) + dp(i - 2)(2)) % mod
      if i > 2 then dp(i)(2) = (dp(i - 3)(0) + dp(i - 3)(1)) % mod
    dp.map(count => count.fold(0)((acc, x) => (acc + x) % mod))
