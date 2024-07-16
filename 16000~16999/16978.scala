import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

class SegmentTree(n: Int, nums: Array[Int]):
  val t = Array.fill(4 * n)(0L)
  build(nums, 1, 0, n - 1)

  def build(nums: Array[Int], v: Int, tl: Int, tr: Int): Unit =
    if tl == tr
    then t(v) = nums(tl)
    else
      val tm = (tl + tr) / 2
      build(nums, 2 * v, tl, tm)
      build(nums, 2 * v + 1, tm + 1, tr)
      t(v) = t(2 * v) + t(2 * v + 1)

  private def sum(v: Int, tl: Int, tr: Int, l: Int, r: Int): Long =
    if l > r then 0
    else if l == tl && r == tr then t(v)
    else
      val tm = (tl + tr) / 2
      sum(2 * v, tl, tm, l, r min tm) +
        sum(2 * v + 1, tm + 1, tr, l max (tm + 1), r)

  def sum(l: Int, r: Int): Long = sum(1, 0, n - 1, l, r)

  private def update(v: Int, tl: Int, tr: Int, pos: Int, new_val: Int): Unit =
    if tl == tr
    then t(v) = new_val
    else
      val tm = (tl + tr) / 2
      if pos <= tm then update(2 * v, tl, tm, pos, new_val)
      else update(2 * v + 1, tm + 1, tr, pos, new_val)
      t(v) = t(2 * v) + t(2 * v + 1)

  def update(pos: Int, new_val: Int): Unit = update(1, 0, n - 1, pos, new_val)

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val n    = input(0).toInt
    val nums = input(1).split(" ").map(_.toInt)
    val m    = input(2).toInt

    val queries = Array.fill(m)(List.empty[(Int, Int, Int)])

    def loop(input: List[Array[Int]], acc: List[(Int, Int)], idx: Int): List[(Int, Int)] =
      input match
        case Nil                  => acc.reverse
        case Array(1, i, v) :: xs => loop(xs, (i, v) :: acc, idx)
        case Array(2, k, i, j) :: xs =>
          queries(k) = (i, j, idx) :: queries(k)
          loop(xs, acc, idx + 1)
        case _ => assert(false)

    val updates = loop(input.drop(3).map(_.split(" ").map(_.toInt)), Nil, 0)

    val segtree = SegmentTree(n, nums)

    var lastQIdx = -1
    val ans = Array.fill(m)(-1L)

    for (l, r, qidx) <- queries(0)
    do 
      ans(qidx) = segtree.sum(l - 1, r - 1)
      lastQIdx = lastQIdx max qidx

    for ((i, v), idx) <- updates.zipWithIndex
    do
      segtree.update(i - 1, v)

      for (l, r, qidx) <- queries(idx + 1)
      do 
        ans(qidx) = segtree.sum(l - 1, r - 1)
        lastQIdx = lastQIdx max qidx

    ans.take(lastQIdx + 1).mkString("\n")
