import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val size = readInt()
    val towers = readLine().split(' ').map(_.toInt)

    val ans = Array.ofDim[Int](size)

    val s = collection.mutable.Stack[Int]()
    for (h, i) <- towers.zipWithIndex
    do
      while s.nonEmpty && towers(s.top) < h do s.pop()
      if s.nonEmpty then ans(i) = s.top + 1
      s.push(i)

    println(ans.mkString(" "))
