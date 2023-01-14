import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    import collection.immutable.ArraySeq

    readInt()
    readLine()
      .split(' ')
      .map(_.toInt)
      .pipe(ArraySeq.unsafeWrapArray(_))
      .pipe(lis)
      .pipe(println)

  def lis(numbers: IndexedSeq[Int]): Int =
    import collection.mutable.ArrayBuffer
    import collection.Searching.*

    val dp = ArrayBuffer.empty[Int]

    for x <- numbers
    do
      dp.search(x) match
        case InsertionPoint(i) =>
          if i == dp.size then dp += x
          else dp(i) = x
        case Found(foundIndex) => ()

    dp.size
