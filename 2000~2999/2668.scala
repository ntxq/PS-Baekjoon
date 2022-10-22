import io.StdIn._
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val numbers =
      for i <- 1 to readInt()
      yield readInt() - 1

    val result = solve(numbers)
    println(result.size)
    println(result.toVector.sorted.mkString("\n"))

  def solve(numbers: IndexedSeq[Int]): Set[Int] =
    @tailrec
    def visit(idx: Int, visited: Vector[Boolean]): Int =
      if visited(numbers(idx)) then numbers(idx)
      else visit(numbers(idx), visited.updated(idx, true))

    val cycles =
      for i <- (0 until numbers.size).toSet
      yield visit(i, Vector.fill(numbers.size)(false))

    @tailrec
    def cycleNodes(start: Int, idx: Int, nodes: Set[Int]): Set[Int] =
      if numbers(idx) == start then nodes + idx
      else cycleNodes(start, numbers(idx), nodes + idx)

    cycles.flatMap(start => cycleNodes(start, start, Set.empty)).map(_ + 1)
