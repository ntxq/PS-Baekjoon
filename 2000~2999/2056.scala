import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()

    val times = Array.fill(n)(0)
    for
      i <- 0 until n
      line = readLine().split(' ').map(_.toInt)
    do
      val cost = line(0)
      times(i) += cost

      for j <- line.indices.drop(2)
      do times(i) = times(i) max (times(line(j) - 1) + cost)

    println(times.max)
