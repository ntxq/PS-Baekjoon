import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val seq = readLine().split(' ').map(_.toInt)

    val m = readInt()
    val queries =
      for _ <- 0 until m
      yield readLine().split(' ').map(_.toInt) match
        case Array(l, r) => (l, r)

    Mo(seq, queries).answers.mkString("\n").pipe(println)

class Mo(seq: Array[Int], queries: Seq[(Int, Int)]):
  val blockSize = Math.sqrt(queries.length).toInt
  val sortedQueries =
    queries.zipWithIndex
      .sortBy { case ((l, r), _) => (l / blockSize, r) }

  val counts = Array.fill(100001)(0)
  val table = Array.fill(100001)(0)
  table(0) = 100001

  var curCount = 0

  private def add(x: Int): Unit =
    // println(s"add $x")
    table(counts(x)) -= 1
    counts(x) += 1
    table(counts(x)) += 1
    curCount = curCount max counts(x)

  private def remove(x: Int): Unit =
    // println(s"remove $x")
    table(counts(x)) -= 1
    if table(curCount) == 0 then curCount -= 1
    counts(x) -= 1
    table(counts(x)) += 1

  final def answers: Array[Int] =
    val result = Array.fill(queries.length)(0)

    val ((s, e), idx) = sortedQueries.head
    for i <- s to e
    do add(seq(i - 1))
    result(idx) = curCount

    sortedQueries.tail.foldLeft((s, e)) { case ((s, e), ((l, r), idx)) =>
      for i <- l until s
      do add(seq(i - 1))

      for i <- e + 1 to r
      do add(seq(i - 1))

      for i <- s until l
      do remove(seq(i - 1))

      for i <- r + 1 to e
      do remove(seq(i - 1))

      result(idx) = curCount

      (l, r)
    }

    result
