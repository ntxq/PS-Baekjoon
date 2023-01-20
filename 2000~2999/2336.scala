import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val firstOrder = readLine().split(' ').map(_.toInt)
    val secondOrder = readLine().split(' ').map(_.toInt)
    val thirdOrder = readLine().split(' ').map(_.toInt)

    val second = Array.ofDim[Int](n)
    (0 until n).foreach(i => second(secondOrder(i) - 1) = i)
    val third = Array.ofDim[Int](n)
    (0 until n).foreach(i => third(thirdOrder(i) - 1) = i)

    var count = 0
    val segtree = SegmentTree(n)

    for
      student <- firstOrder
      secondIdx = second(student - 1)
      thirdIdx = third(student - 1)
      if segtree.query(secondIdx, thirdIdx)
    do count += 1

    println(count)

class SegmentTree(n: Int):
  val tree = Array.fill(n * 4)(Int.MaxValue)

  private def query(v: Int, tl: Int, tr: Int, l: Int, r: Int): Int =
    if l > r then Int.MaxValue
    else if l == tl && tr == r then tree(v)
    else
      val tm = (tl + tr) / 2
      query(v * 2, tl, tm, l, Math.min(r, tm)) min
        query(v * 2 + 1, tm + 1, tr, Math.max(l, tm + 1), r)

  private def update(v: Int, tl: Int, tr: Int, pos: Int, data: Int): Unit =
    if tl == tr then tree(v) = data
    else
      tree(v) = tree(v) min data
      val tm = (tl + tr) / 2
      if pos <= tm then update(v * 2, tl, tm, pos, data)
      else update(v * 2 + 1, tm + 1, tr, pos, data)

  final def query(second: Int, third: Int): Boolean =
    val isExcellent = query(1, 0, n - 1, 0, second - 1) > third
    update(1, 0, n - 1, second, third)
    isExcellent
