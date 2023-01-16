import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(min, max) = readLine().split(' ').map(_.toLong)
    println(countSquareFree(min, max))

  def countSquareFree(min: Long, max: Long): Int =
    val numbers = Array.fill((max - min + 1).toInt)(true)

    for i <- LazyList.from(2).map(x => x.toLong * x).takeWhile(_ <= max) do
      val x = (min / i) * i
      for j <- (if x < min then x + i else x) to max by i do
        numbers((j - min).toInt) = false

    numbers.count(identity)

    