import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    for _ <- 0 until readInt()
    do
      readLine()
        .split(' ')
        .map(_.toInt)
        .pipe { case Array(x, y) =>
          countFlight(y - x)
        }
        .pipe(println)

  def countFlight(dist: Int): Long =
    val n = LazyList.from(1).find(n => n.toLong * (n + 1) >= dist).get.toLong
    if n * n < dist then n * 2 else n * 2 - 1
