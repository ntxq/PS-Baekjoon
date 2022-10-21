import io.StdIn._
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    println(
      (for
        _ <- (0 until readInt())
        pwd = readLine()
      yield 6 <= pwd.length && pwd.length <= 9)
        .map(if _ then "yes" else "no")
        .mkString("\n")
    )
