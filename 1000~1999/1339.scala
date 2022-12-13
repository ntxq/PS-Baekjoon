import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    (for _ <- (0 until n).toList
    yield readLine().mkString).pipe(MaxWordSum(_)).pipe(_.maxSum).tap(println)

class MaxWordSum(val words: List[String]):
  def maxSum: Int =
    val scores: mutable.Map[Char, Int] = mutable.Map.empty.withDefault(_ => 0)

    for
      word <- words
      (c, s) <- word.reverse.zipWithIndex
    do scores(c) = scores(c) + math.pow(10, s).toInt

    val assignment = mutable.Map.empty[Char, Int]
    for (c, s) <- scores.toSeq.sortBy(_._2).map(_._1).reverse.zipWithIndex
    do assignment(c) = 9 - s

    words.map(_.map(assignment).mkString.toInt).sum
