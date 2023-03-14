import io.StdIn.*
import annotation.tailrec
import util.chaining.*

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine().split(' ').map(_.toInt)

    val baskets = LazyList.range(1, n + 1)

    def loop(baskets: LazyList[Int], m: Int): LazyList[Int] =
      if m == 0 then baskets
      else
        val Array(i, j, k) = readLine().split(' ').map(_.toInt)

        val (prefix, middle) = baskets.splitAt(i - 1)
        val (target, suffix) = middle.splitAt(j - i + 1)
        val (before, after) = target.splitAt(k - i)

        loop(prefix #::: after #::: before #::: suffix, m - 1)

    loop(baskets, m).pipe(_.mkString(" ")).pipe(println)
