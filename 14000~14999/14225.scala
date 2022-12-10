import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    readLine()
      .split(" ")
      .map(_.toInt)
      .toVector
      .pipe(subsequenceSum)
      .pipe(println)

  def subsequenceSum(arr: Vector[Int]): Int =
    def loop(arr: Vector[Int]): Set[Int] =
      arr match
        case x +: xs =>
          val sums = loop(xs)
          sums ++ sums.map(_ + x)
        case _ => Set(0)

    val allSums = loop(arr)
    LazyList.from(1).find(!allSums.contains(_)).get
