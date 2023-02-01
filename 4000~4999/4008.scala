import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val Array(a, b, c) = readLine().split(' ').map(_.toLong)

    val prefixSums = readLine().split(' ').map(_.toLong).scanLeft(0L)(_ + _)

    val dp = Array.ofDim[Long](n + 1)
    val xPos = Array.ofDim[Int](n + 1)
    val stack = Array.ofDim[Int](n + 1)

    def getModified(x: Long): Long =
      a * x * x + b * x + c
    def getSlope(i: Int): Long =
      -2 * a * prefixSums(i)
    def getIntercept(i: Int): Long =
      a * prefixSums(i) * prefixSums(i) - b * prefixSums(i) + dp(i)
    def getCrossPoint(p: Int, q: Int): Double =
      val k1 = getSlope(p)
      val m1 = getIntercept(p)
      val k2 = getSlope(q)
      val m2 = getIntercept(q)
      (m1 - m2).toDouble / (k2 - k1)

    var stackSize = 0
    var maxPoint = 1
    for i <- 1 to n
    do
      dp(i) = getModified(prefixSums(i))
      if stackSize > 0 then
        while maxPoint < stackSize && xPos(maxPoint + 1) < prefixSums(i) do
          maxPoint += 1
        val j = stack(maxPoint)
        dp(i) = dp(i) max dp(j) + getModified(prefixSums(i) - prefixSums(j))

        while stackSize > 1 && xPos(stackSize) > getCrossPoint(
            stack(stackSize),
            i
          )
        do stackSize -= 1
        stackSize += 1
        stack(stackSize) = i
        xPos(stackSize) = getCrossPoint(stack(stackSize - 1), i).toInt
        if maxPoint > stackSize then maxPoint = stackSize
      else
        stackSize = 1
        stack(1) = i
        xPos(1) = Int.MinValue

    println(dp(n))
