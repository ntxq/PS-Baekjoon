import scala.io.StdIn.{readLine, readInt}

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val aMap = readLine().split(" ").map(_.toInt).zipWithIndex.toMap
    val b = readLine().split(" ").map(_.toInt)

    val tree = SegmentTree(n)

    val count =
      for i <- b
      yield tree.update(1, 0, n - 1, aMap(i))
    println(count.sum)

class SegmentTree(size: Int):
  val tree = Array.fill(size * 4)(0L)

  def query(v: Int, tl: Int, tr: Int, l: Int, r: Int): Long =
    if l > r then 0
    else if tl == l && tr == r then tree(v)
    else
      val tm = (tl + tr) / 2
      query(v * 2, tl, tm, l, r min tm)
        + query(v * 2 + 1, tm + 1, tr, l max (tm + 1), r)

  def update(v: Int, tl: Int, tr: Int, pos: Int): Long =
    if tl == tr then
      tree(v) = 1
      query(1, 0, size - 1, pos + 1, size - 1)
    else
      val tm = (tl + tr) / 2
      if pos <= tm then
        val qVal = update(v * 2, tl, tm, pos)
        tree(v) = tree(v * 2) + tree(v * 2 + 1)
        qVal
      else
        val qVal = update(v * 2 + 1, tm + 1, tr, pos)
        tree(v) = tree(v * 2) + tree(v * 2 + 1)
        qVal
