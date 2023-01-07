import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    import scala.collection.immutable.ArraySeq

    readInt()
    println(
      parametricSearch(
        readLine().split(' ').map(_.toInt).pipe(ArraySeq.unsafeWrapArray),
        readInt()
      )
    )

  def parametricSearch(requests: Seq[Int], budget: Int): Int =
    var low = 0
    var high = requests.max
    
    while low < high do
      val mid = (low + high + 1) / 2      
      if requests.map(_ min mid).sum <= budget then
        low = mid
      else
        high = mid - 1

    low

    
