import scala.io.StdIn.{readLine, readInt}

object Main:
  def main(args: Array[String]): Unit =
    val (n, m) = readLine().split(" ").map(_.toInt) match
      case Array(n, m) => (n, m)

    val a =
      for _ <- 0 until n
      yield readLine().split(" ").map(_.toInt)

    val b =
      for _ <- 0 until n
      yield readLine().split(" ").map(_.toInt)

    val c =
      for (arow, brow) <- a.zip(b)
      yield for (acol, bcol) <- arow.zip(brow)
      yield acol + bcol

    for crow <- c
    do
      for ccol <- crow
      do print(ccol + " ")
      println()
