import io.StdIn._
import collection.mutable

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, s) = readLine().split(" ").map(_.toInt)
    val numbers = readLine().split(" ").map(_.toInt)

    println((for
      subarray <- 1 until (1 << n)
      sum = (
        for
          i <- 0 until n
          if (subarray & (1 << i)) != 0
        yield numbers(i)
      ).sum
      if sum == s
    yield true).size)
