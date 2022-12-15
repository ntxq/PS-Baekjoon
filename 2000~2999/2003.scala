import io.StdIn.*
import scala.annotation.tailrec
import collection.mutable

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine().split(" ").map(_.toInt)
    val inputSeq = readLine().split(" ").map(_.toInt)

    println(countSum(m, inputSeq))

  def countSum(target: Int, seq: Array[Int]): Int =
    @tailrec
    def loop(left: Int, right: Int, curSum: Int, count: Int): Int =
      if curSum > target then loop(left + 1, right, curSum - seq(left), count)
      else if right == seq.length then
        count + (if curSum == target then 1 else 0)
      else if curSum == target then
        loop(left + 1, right + 1, curSum - seq(left) + seq(right), count + 1)
      else loop(left, right + 1, curSum + seq(right), count)

    loop(0, 0, 0, 0)
