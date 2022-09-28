import scala.io.StdIn.{readLine, readInt}
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val size = 1000001
    val tree = SegmentTree(size)
    val n = readInt()

    for _ <- 0 until n do
      val op :: xs = readLine().split("\\s+").map(_.toInt).toList
      if op == 1 then println(tree.query(1, 0, size - 1, xs.head))
      else tree.update(1, 0, size - 1, xs.head, xs.last)

case class SegmentTree(size: Int):
  private val t = Array.fill(4 * size)(0)

  @tailrec
  final def update(v: Int, tl: Int, tr: Int, pos: Int, amount: Int): Unit =
    t(v) += amount
    if tl == tr then return
    else
      val tm = (tl + tr) / 2
      if pos <= tm then update(v * 2, tl, tm, pos, amount)
      else update(v * 2 + 1, tm + 1, tr, pos, amount)

  @tailrec
  final def query(v: Int, tl: Int, tr: Int, order: Int): Int =
    t(v) -= 1
    if tl == tr then tl
    else
      val tm = (tl + tr) / 2
      if order <= t(v * 2) then query(v * 2, tl, tm, order)
      else query(v * 2 + 1, tm + 1, tr, order - t(v * 2))
