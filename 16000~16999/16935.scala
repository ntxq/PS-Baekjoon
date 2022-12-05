import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m, r) = readLine().split(" ").map(_.toInt)
    Matrix(
      (for _ <- (0 until n)
      yield readLine().split(" ").map(_.toInt).toVector).toVector
    )
      .pipe(matrix =>
        readLine()
          .split(" ")
          .map(_.toInt)
          .foldLeft(matrix)((matrix, i) =>
            i match
              case 1 => matrix.verticalFlip
              case 2 => matrix.horizontalFlip
              case 3 => matrix.rightTurn
              case 4 => matrix.leftTurn
              case 5 => matrix.rightPartitionTurn
              case 6 => matrix.leftPartitionTurn
          )
      )
      .pipe(_.data.map(_.mkString(" ")).mkString("\n"))
      .pipe(println)

case class Matrix(data: Vector[Vector[Int]]):
  def verticalFlip: Matrix =
    Matrix(data.reverse)

  def horizontalFlip: Matrix =
    Matrix(data.map(_.reverse))

  def rightTurn: Matrix =
    Matrix(data.transpose.map(_.reverse))

  def leftTurn: Matrix =
    Matrix(data.transpose.reverse)

  def split: (
      Vector[Vector[Int]],
      Vector[Vector[Int]],
      Vector[Vector[Int]],
      Vector[Vector[Int]]
  ) =
    val (top, bottom) = data.splitAt(data.size / 2)
    val (first, second) = top.map(_.splitAt(top.head.size / 2)).unzip
    val (fourth, third) = bottom.map(_.splitAt(bottom.head.size / 2)).unzip
    (first, second, third, fourth)

  def rightPartitionTurn: Matrix =
    val (first, second, third, fourth) = split
    val top = fourth.zip(first).map { (a, b) => a ++ b }
    val bottom = third.zip(second).map { (a, b) => a ++ b }
    Matrix(top ++ bottom)

  def leftPartitionTurn: Matrix =
    val (first, second, third, fourth) = split
    val top = second.zip(third).map { (a, b) => a ++ b }
    val bottom = first.zip(fourth).map { (a, b) => a ++ b }
    Matrix(top ++ bottom)
