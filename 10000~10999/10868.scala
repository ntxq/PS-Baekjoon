import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine.split(' ').map(_.toInt)

    val values = Array.ofDim[Int](n)
    for i <- 0 until n
    do values(i) = readInt()

    val segTree = SegmentTree(values)
    (for
      _ <- 0 until m
      Array(l, r) = readLine.split(' ').map(_.toInt)
    yield segTree.query(l - 1, r - 1)).mkString("\n").pipe(println)

class SegmentTree(values: Array[Int]):
  val n = values.length
  val tree = Array.ofDim[Int](4 * n)
  build(1, 0, n - 1)

  private def build(v: Int, tl: Int, tr: Int): Unit =
    if tl == tr then tree(v) = values(tl)
    else
      val tm = (tl + tr) / 2
      build(2 * v, tl, tm)
      build(2 * v + 1, tm + 1, tr)
      tree(v) = tree(2 * v) min tree(2 * v + 1)

  private def query(v: Int, tl: Int, tr: Int, l: Int, r: Int): Int =
    if l > r then Int.MaxValue
    else if l == tl && r == tr then tree(v)
    else
      val tm = (tl + tr) / 2
      query(2 * v, tl, tm, l, r min tm) min
        query(2 * v + 1, tm + 1, tr, l max (tm + 1), r)

  final def query(l: Int, r: Int): Int = query(1, 0, n - 1, l, r)
