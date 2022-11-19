import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    println(backtrack(readInput()).mkString(" "))

  def readInput(): Vector[Vector[Char]] =
    val n = readInt()
    val signs = readLine()

    @tailrec def loop(
        signs: String,
        idx: Int,
        acc: Vector[Vector[Char]]
    ): Vector[Vector[Char]] =
      val (sign, rest) = signs.splitAt(idx)
      if rest.isEmpty then acc :+ sign.toVector
      else loop(rest, idx - 1, acc :+ sign.toVector)

    loop(signs, n, Vector.empty)

  def backtrack(signs: Vector[Vector[Char]]): Vector[Int] =
    @tailrec
    def check(constraint: Vector[Char], seq: Vector[Int], sum: Int): Boolean =
      (constraint, seq) match
        case (Vector(), Vector()) => true
        case (sign +: signs, num +: nums) =>
          sign match
            case '+' => sum + num > 0 && check(signs, nums, sum + num)
            case '-' => sum + num < 0 && check(signs, nums, sum + num)
            case '0' => sum + num == 0 && check(signs, nums, sum + num)
        case _ => false

    def loop(seq: Vector[Int]): Option[Vector[Int]] =
      if seq.length == signs.length then Some(seq)
      else
        val constraint = signs(signs.length - seq.length - 1)
        LazyList
          .range(-10, 11)
          .map(_ +: seq)
          .filter(check(constraint, _, 0))
          .flatMap(loop)
          .headOption

    loop(Vector()).get
