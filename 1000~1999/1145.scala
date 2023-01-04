import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val factors = readLine().split(" ").map(_.toInt).toSeq
    println(almostLCM(factors))

  def almostLCM(factors: Seq[Int]): Int =
    LazyList.from(1)
      .filter(n => factors.count(n % _ == 0) > 2)
      .head