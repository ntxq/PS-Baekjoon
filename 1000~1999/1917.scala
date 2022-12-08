import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    for _ <- 0 until 3
    do
      println(
        if CubeMap.checkCube(
            Vector.fill(6)(readLine().filter(_ != ' ').mkString)
          )
        then "yes"
        else "no"
      )

object CubeMap:
  private val cubes = Vector(
    Vector("0010", "1111", "0010"),
    Vector("0100", "1111", "1000"),
    Vector("0010", "1111", "0100"),
    Vector("0001", "1111", "1000"),
    Vector("0001", "1111", "0100"),
    Vector("11100", "00111"),
    Vector("1100", "0111", "0010"),
    Vector("1100", "0111", "0001"),
    Vector("0010", "1110", "0011"),
    Vector("0001", "1111", "0001"),
    Vector("1100", "0110", "0011")
  )

  val allCubes: Vector[Vector[String]] =
    def turn(cube: Vector[String]): Vector[String] =
      cube.transpose.reverse.map(_.mkString)

    val normal = cubes
    val rotated90 = normal.map(turn)
    val rotated180 = rotated90.map(turn)
    val rotated270 = rotated180.map(turn)

    val flipped = cubes.map(_.reverse)
    val flippedAndRotated90 = flipped.map(turn)
    val flippedAndRotated180 = flippedAndRotated90.map(turn)
    val flippedAndRotated270 = flippedAndRotated180.map(turn)

    normal ++
      rotated90 ++
      rotated180 ++
      rotated270 ++
      flipped ++
      flippedAndRotated90 ++
      flippedAndRotated180 ++
      flippedAndRotated270

  def checkCube(input: Vector[String]): Boolean =
    allCubes.exists(cube =>
      (0 until 6 - cube.length + 1).exists(rows =>
        (0 until 6 - cube.head.length + 1).exists(cols =>
          input
            .slice(rows, rows + cube.length)
            .map(_.slice(cols, cols + cube.head.length)) == cube
        )
      )
    )
