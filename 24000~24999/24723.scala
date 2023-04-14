extension [A, B](x: A) def |>(f: A => B): B = f(x)

object Main:
  def main(args: Array[String]): Unit =
    (0 until io.StdIn.readInt()).foldLeft(1)((acc, _) => acc * 2) |> println
