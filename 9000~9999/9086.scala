import scala.io.StdIn.{readLine, readInt}

object Main:
  def main(args: Array[String]): Unit =
    for _ <- 0 until readInt()
    do
      val input = readLine()
      println(
        s"${input.head}${input.last}"
      )
