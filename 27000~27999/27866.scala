import io.StdIn.*
import annotation.tailrec

extension [A](self: A) def |>[B](f: A => B): B = f(self)

object Main:
  def main(args: Array[String]): Unit =
    readLine().charAt(readInt() - 1) |> println
