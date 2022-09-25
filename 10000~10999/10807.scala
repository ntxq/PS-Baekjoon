import scala.io.StdIn

object Main:
  def main(args: Array[String]): Unit =
    val N = StdIn.readInt()
    val A = StdIn.readLine().split("\\s+").map(_.toInt)
    val v = StdIn.readInt()

    val count = A.count(_ == v)
    println(count)
