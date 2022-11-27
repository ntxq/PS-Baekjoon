import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val target = readInt()
    val costs = readLine().split(" ").map(_.toInt)
    println(maxCost(target, costs))

  def maxCost(target: Int, costs: Array[Int]): Int =
    @tailrec
    def loop(dp: Vector[Int]): Int =
      if dp.size == target + 1 then dp.last
      else
        val cost = costs.indices
          .withFilter(i => dp.size - i - 1 >= 0)
          .map(i => dp(dp.size - i - 1) + costs(i))
          .max
        loop(dp :+ cost)

    loop(Vector(0))
