import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    println(maxDiff(readLine().split(" ").map(_.toInt)))

  def maxDiff(seq: Array[Int]): Int =
    seq.permutations.map(_.sliding(2).map(_.reduce(_ - _)).map(_.abs).sum).max
