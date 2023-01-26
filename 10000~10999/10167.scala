import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    import collection.mutable.ArrayBuffer

    val n = readInt()

    val xs = Array.ofDim[Long](n)
    val ys = Array.ofDim[Long](n)
    val rawMines = Array.ofDim[(Long, Long, Long)](n)
    for
      i <- 0 until n
      Array(x, y, profit) = readLine().split(' ').map(_.toLong)
    do
      xs(i) = x
      ys(i) = y
      rawMines(i) = (x, y, profit)

    val distinctXs = xs.distinct.sorted
    val distinctYs = ys.distinct.sorted
    val mines = rawMines
      .map((x, y, profit) =>
        val xIdx = distinctXs.search(x).insertionPoint
        val yIdx = distinctYs.search(y).insertionPoint
        (xIdx, yIdx, profit)
      )
      .sortBy(m => m._2)

    var maxProfit = Long.MinValue
    val segmentTree = SegmentTree(mines.length)

    for
      i <- 0 until n
      if i == 0 || mines(i)._2 != mines(i - 1)._2
    do
      segmentTree.clear()
      for j <- i until n
      do
        segmentTree.update(mines(j)._1, mines(j)._3)
        if j == n - 1 || mines(j)._2 != mines(j + 1)._2 then
          maxProfit = maxProfit max segmentTree.answer

    println(maxProfit)

class SegmentTree(n: Int):
  case class Data(sum: Long, prefix: Long, suffix: Long, answer: Long)
  object Data:
    def apply(value: Long): Data =
      val v = value max 0
      Data(value, v, v, v)

    extension (lhs: Data)
      def +(rhs: Long): Data =
        val value = lhs.sum + rhs
        val v = value max 0
        Data(value, v, v, v)

      infix def combine(rhs: Data): Data =
        Data(
          sum = lhs.sum + rhs.sum,
          prefix = lhs.prefix max (lhs.sum + rhs.prefix),
          suffix = rhs.suffix max (rhs.sum + lhs.suffix),
          answer = lhs.answer max rhs.answer max (lhs.suffix + rhs.prefix)
        )

  private val tree = Array.ofDim[Data](4 * n)

  final def clear(): Unit =
    tree.indices.foreach(i => tree(i) = Data(0, 0, 0, 0))

  private def update(v: Int, tl: Int, tr: Int, pos: Int, value: Long): Unit =
    if tl == tr then tree(v) += value
    else
      val tm = (tl + tr) / 2
      if pos <= tm then update(2 * v, tl, tm, pos, value)
      else update(2 * v + 1, tm + 1, tr, pos, value)
      tree(v) = tree(2 * v) combine tree(2 * v + 1)

  final def update(pos: Int, value: Long): Unit =
    update(1, 0, n - 1, pos, value)

  final def answer: Long =
    tree(1).answer
