import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    val k = readInt()
    val seq = readLine().split(" ").map(_.toInt).toVector
    nextPermutation(seq) match
      case Some(p) => println(p.mkString(" "))
      case None    => println(-1)

  def nextPermutation(xs: Vector[Int]): Option[Vector[Int]] =
    val pivot = xs.zip(xs.tail).lastIndexWhere((a, b) => a < b)

    if pivot == -1 then None
    else
      val successor = xs.lastIndexWhere(_ > xs(pivot))
      Some(
        (xs.take(pivot) :+ xs(successor)) ++
          ((xs.slice(pivot + 1, successor) :+ xs(pivot)) ++
            xs.drop(successor + 1)).reverse
      )
