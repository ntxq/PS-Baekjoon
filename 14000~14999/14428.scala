import scala.io.StdIn.{readLine, readInt}

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val elems = readLine().split("\\s+").map(_.toInt)
    val tree = SegmentTree(elems)

    val m = readInt()
    for _ <- 0 until m do
      val Array(a, b, c) = readLine().split("\\s+").map(_.toInt)
      if a == 1 then tree.update(b, c)
      else println(tree(b, c))

class SegmentTree(elems: Array[Int]):
  case class Node(var value: Int, var index: Int)
  private val tree = Array.fill(elems.length * 4)(Node(Int.MaxValue, -1))

  private def build(v: Int, tl: Int, tr: Int): Unit =
    if tl == tr then tree(v) = Node(elems(tl), tl)
    else
      val tm = (tl + tr) / 2
      build(v * 2, tl, tm)
      build(v * 2 + 1, tm + 1, tr)
      tree(v) =
        if tree(v * 2).value <= tree(v * 2 + 1).value then tree(v * 2)
        else tree(v * 2 + 1)

  private def query(v: Int, tl: Int, tr: Int, l: Int, r: Int): Node =
    if l > r then Node(Int.MaxValue, -1)
    else if l == tl && r == tr then tree(v)
    else
      val tm = (tl + tr) / 2
      val left = query(v * 2, tl, tm, l, Math.min(r, tm))
      val right = query(v * 2 + 1, tm + 1, tr, Math.max(l, tm + 1), r)
      if left.value <= right.value then left else right

  private def update(v: Int, tl: Int, tr: Int, pos: Int, newVal: Int): Unit =
    if tl == tr then tree(v) = Node(newVal, pos)
    else
      val tm = (tl + tr) / 2
      if pos <= tm then update(v * 2, tl, tm, pos, newVal)
      else update(v * 2 + 1, tm + 1, tr, pos, newVal)
      tree(v) =
        if tree(v * 2).value <= tree(v * 2 + 1).value then tree(v * 2)
        else tree(v * 2 + 1)

  def apply(l: Int, r: Int): Int =
    query(1, 0, elems.length - 1, l - 1, r - 1).index + 1

  def update(pos: Int, newVal: Int): Unit =
    update(1, 0, elems.length - 1, pos - 1, newVal)

  build(1, 0, elems.length - 1)
