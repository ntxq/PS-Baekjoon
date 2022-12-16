import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    if dokiSnack(readLine().split(" ").map(_.toInt)) then println("Nice")
    else println("Sad")

  def dokiSnack(queue: Array[Int]): Boolean =
    @tailrec
    def shuntingYard(from: List[Int], yard: List[Int], next: Int): Boolean =
      (from, yard) match
        case (Nil, Nil)                => true
        case (x :: xs, _) if x == next => shuntingYard(xs, yard, next + 1)
        case (_, y :: ys) if y == next => shuntingYard(from, ys, next + 1)
        case (x :: xs, _)              => shuntingYard(xs, x :: yard, next)
        case _                         => false

    import scala.collection.immutable.ArraySeq
    shuntingYard(ArraySeq.unsafeWrapArray(queue).toList, Nil, 1)
