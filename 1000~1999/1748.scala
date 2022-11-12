import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    println(
      countLength(
        readInt()
      )
    )

  def countLength(n: Int): Int =
    LazyList.iterate(1)(_ * 10).takeWhile(_ <= n).map(n - _ + 1).sum
