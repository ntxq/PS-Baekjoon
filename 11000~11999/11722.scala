import io.StdIn.*
import scala.collection.mutable
import scala.collection.Searching._

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    println(lds(readLine().split(" ").map(_.toInt)))

  def lds(xs: Array[Int]): Int =
    val dp = mutable.ArrayBuffer.empty[Int]
    given Ordering[Int] = Ordering.Int.reverse

    for x <- xs
    do
      dp.search(x) match
        case Found(i) =>
          dp(i) = x
        case InsertionPoint(i) if i == dp.size =>
          dp += x
        case InsertionPoint(i) =>
          dp(i) = x
    dp.size
