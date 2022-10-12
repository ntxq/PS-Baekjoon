import scala.io.StdIn.{readLine, readInt}

object Main:
  def main(args: Array[String]): Unit =
    println(
      for c <- readLine()
      yield
        if c.isUpper then c.toLower
        else c.toUpper
    )
