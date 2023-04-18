extension [A, B](x: A) def |>(f: A => B): B = f(x)

object Main:
  def main(args: Array[String]): Unit =
    def fact(n: Int, acc: Long): Long =
      if n == 0 then acc
      else fact(n - 1, n * acc)
    fact(io.StdIn.readInt(), 1) |> println
