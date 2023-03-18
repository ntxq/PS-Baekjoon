import io.StdIn.*
import annotation.tailrec
import util.chaining.*

object Main:
  def main(args: Array[String]): Unit =
    (for x <- io.Source.stdin.getLines().map(_.toInt).takeWhile(_ != -1)
    yield
      val factors =
        for
          i <- 1 until x
          if x % i == 0
        yield i

      if factors.sum == x then s"$x = ${factors.mkString("", " + ", "")}"
      else s"$x is NOT perfect."
    ).mkString("\n").pipe(println)
