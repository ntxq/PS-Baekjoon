import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    import scala.collection.immutable.ArraySeq

    readInt()
    val xs = readLine().split(" ").map(_.toInt).pipe(ArraySeq.unsafeWrapArray)
    val ys = readLine().split(" ").map(_.toInt).pipe(ArraySeq.unsafeWrapArray)
    println(minSumOfProduct(xs, ys))

  def minSumOfProduct(xs: Seq[Int], ys: Seq[Int]): Int =
    xs.sorted.reverse
      .zip(ys.sorted)
      .foldLeft(0) { case (acc, (x, y)) => acc + x * y }
