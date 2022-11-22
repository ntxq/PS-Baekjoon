import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    println(allPermutations(readInt()))

  def allPermutations(n: Int): String =
    Vector.range(1, n + 1).permutations.map(_.mkString(" ")).mkString("\n")
