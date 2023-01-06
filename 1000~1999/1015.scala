import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    readInt()
    readLine()
      .pipe(_.split(' '))
      .map(_.toInt)
      .toVector
      .pipe(descendingOrder)
      .mkString(" ")
      .pipe(println)

  def descendingOrder(xs: Vector[Int]): Vector[Int] =
    xs.zipWithIndex
      .sortBy((x, _) => x)
      .map((_, i) => i)
      .zipWithIndex
      .foldLeft(Vector.fill(xs.length)(0)) { case (acc, (i, j)) =>
        acc.updated(i, j)
      }
