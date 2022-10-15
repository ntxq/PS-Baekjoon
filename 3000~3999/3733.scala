import scala.io.StdIn.{readLine, readInt}

object Main:
  def main(args: Array[String]): Unit =
    for line <- Iterator.continually(readLine).takeWhile(_ != null)
    do
      line.split(" ") match
        case Array(n, s) => println(s.toInt / (n.toInt + 1))
