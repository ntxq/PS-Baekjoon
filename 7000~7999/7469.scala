import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine().split(' ').map(_.toInt)
    val data = readLine().split(' ').map(_.toInt)
    val sortTree = MergeSortTree(data)

    (for
      _ <- 0 until m
      Array(a, b, c) = readLine().split(' ').map(_.toInt)
    yield
      var left = -1000000000
      var right = 1000000000
      while left <= right do
        val mid = (left + right) / 2
        val count = sortTree.query(a, b, mid)

        if count < c then left = mid + 1
        else right = mid - 1
      left
    ).mkString("\n").pipe(println)

class MergeSortTree(data: Array[Int]):
  import collection.mutable.ArrayBuffer
  val tree = Array.ofDim[Array[Int]](data.length * 4)
  build(1, 0, data.length - 1)

  private def merge(v: Int, left: Int, right: Int): Unit =
    val merged = ArrayBuffer.empty[Int]

    var i = 0
    var j = 0

    while i < tree(left).length && j < tree(right).length do
      if tree(left)(i) < tree(right)(j) then
        merged += tree(left)(i)
        i += 1
      else
        merged += tree(right)(j)
        j += 1

    while i < tree(left).length do
      merged += tree(left)(i)
      i += 1

    while j < tree(right).length do
      merged += tree(right)(j)
      j += 1

    tree(v) = merged.toArray

  private def build(v: Int, tl: Int, tr: Int): Unit =
    if tl == tr then tree(v) = Array(data(tl))
    else
      val tm = (tl + tr) / 2
      build(v * 2, tl, tm)
      build(v * 2 + 1, tm + 1, tr)
      merge(v, v * 2, v * 2 + 1)

  private def query(v: Int, tl: Int, tr: Int, l: Int, r: Int, k: Int): Int =
    import collection.Searching.*

    if l > r then 0
    else if l == tl && tr == r then
      tree(v).search(k) match
        case Found(foundIndex)              => foundIndex + 1
        case InsertionPoint(insertionPoint) => insertionPoint
    else
      val tm = (tl + tr) / 2
      query(v * 2, tl, tm, l, Math.min(r, tm), k) +
        query(v * 2 + 1, tm + 1, tr, Math.max(l, tm + 1), r, k)

  final def query(l: Int, r: Int, k: Int): Int =
    query(1, 0, data.length - 1, l - 1, r - 1, k)
