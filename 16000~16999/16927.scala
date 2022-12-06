import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m, r) = readLine.split(" ").map(_.toInt)
    val data =
      for _ <- (0 until n).toArray
      yield readLine.split(" ").map(_.toInt)
    Matrix(data, n, m)
      .tap(_.turn(r))
      .pipe(_.data.map(_.mkString(" ")).mkString("\n"))
      .pipe(println)

class Matrix(val data: Array[Array[Int]], val rows: Int, val cols: Int):
  def turnRing(ring: Int): Unit =
    val temp = data(ring)(ring)

    // top left to top right
    for i <- ring until cols - ring - 1
    do data(ring)(i) = data(ring)(i + 1)

    // top right to bottom right
    for i <- ring until rows - ring - 1
    do data(i)(cols - ring - 1) = data(i + 1)(cols - ring - 1)

    // bottom right to bottom left
    for i <- cols - ring - 1 to ring + 1 by -1
    do data(rows - ring - 1)(i) = data(rows - ring - 1)(i - 1)

    // bottom left to top left
    for i <- rows - ring - 1 to ring + 1 by -1
    do data(i)(ring) = data(i - 1)(ring)

    data(ring + 1)(ring) = temp

  def turn(times: Int): Unit =
    for
      ring <- 0 until (rows min cols) / 2
      ringSize = (rows - 2 * ring) * 2 + (cols - 2 * ring - 2) * 2
      turns = times % ringSize
      _ <- 0 until turns
    do turnRing(ring)
