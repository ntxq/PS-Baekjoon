import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val data = readLine().split(' ').map(_.toInt)

    val segmentTree = SegmentTree(data)

    val ans = collection.mutable.ListBuffer.empty[Long]
    val m = readInt()
    for
      _ <- 0 until m
      ops = readLine().split(' ').map(_.toInt)
    do
      ops match
        case Array(1, l, r, addend) =>
          segmentTree.update(l - 1, r - 1, 1, addend)
        case Array(2, l, r, factor) =>
          segmentTree.update(l - 1, r - 1, factor, 0)
        case Array(3, l, r, assignment) =>
          segmentTree.update(l - 1, r - 1, 0, assignment)
        case Array(4, l, r) =>
          ans += segmentTree.query(l - 1, r - 1)

    ans.mkString("\n").pipe(println)

class SegmentTree(data: Array[Int]):
  val mod = 1000000007L

  val n = data.length
  val tree = Array.ofDim[Long](data.length * 4)
  val lazyProduct = Array.fill[Long](data.length * 4)(1L)
  val lazyAddition = Array.ofDim[Long](data.length * 4)
  build(1, 0, n - 1)

  private def build(v: Int, tl: Int, tr: Int): Unit =
    if tl == tr then tree(v) = data(tl)
    else
      val tm = (tl + tr) / 2
      build(v * 2, tl, tm)
      build(v * 2 + 1, tm + 1, tr)
      tree(v) = (tree(v * 2) + tree(v * 2 + 1)) % mod

  private def push(v: Int, tl: Int, tr: Int): Unit =
    val a = lazyProduct(v)
    val b = lazyAddition(v)

    if tl != tr then
      for child <- List(v * 2, v * 2 + 1)
      do
        lazyProduct(child) = (lazyProduct(child) * a) % mod
        lazyAddition(child) = (lazyAddition(child) * a + b) % mod

    tree(v) = (tree(v) * a + b * (tr - tl + 1)) % mod
    lazyProduct(v) = 1
    lazyAddition(v) = 0

  private def update(
      v: Int,
      tl: Int,
      tr: Int,
      l: Int,
      r: Int,
      factor: Long,
      addend: Long
  ): Unit =
    push(v, tl, tr)
    if l > r then ()
    else if l == tl && tr == r then
      lazyProduct(v) = (lazyProduct(v) * factor) % mod
      lazyAddition(v) = (lazyAddition(v) * factor + addend) % mod
      push(v, tl, tr)
    else
      val tm = (tl + tr) / 2
      update(v * 2, tl, tm, l, r min tm, factor, addend)
      update(v * 2 + 1, tm + 1, tr, l max (tm + 1), r, factor, addend)
      tree(v) = (tree(v * 2) + tree(v * 2 + 1)) % mod

  private def query(v: Int, tl: Int, tr: Int, l: Int, r: Int): Long =
    push(v, tl, tr)
    if l > r then 0
    else if l == tl && tr == r then tree(v) % mod
    else
      val tm = (tl + tr) / 2
      (query(v * 2, tl, tm, l, r min tm) +
        query(v * 2 + 1, tm + 1, tr, l max (tm + 1), r)) % mod

  final def update(l: Int, r: Int, factor: Long, addend: Long): Unit =
    update(1, 0, n - 1, l, r, factor, addend)

  final def query(l: Int, r: Int): Long =
    query(1, 0, n - 1, l, r)
