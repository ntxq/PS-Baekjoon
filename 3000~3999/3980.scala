import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    (for _ <- 0 until readInt()
    yield (Ferguson(
      for _ <- (0 until 11).toArray
      yield readLine().split(" ").map(_.toInt)
    )).maxSum).foreach(println)

class Ferguson(weights: Array[Array[Int]]):
  val possibleWeights: Vector[Vector[(Int, Int)]] =
    weights
      .map(player =>
        (0 until 11).filter(player(_) > 0).map(i => (i, player(i))).toVector
      )
      .toVector

  final def maxSum: Int =
    def loop(
        players: Vector[Vector[(Int, Int)]],
        visited: Set[Int],
        acc: Int
    ): Option[Int] =
      players match
        case x +: xs =>
          x.filterNot((i, w) => visited.contains(i))
            .flatMap((i, w) => loop(xs, visited + i, acc + w))
            .maxOption
        case _ => Some(acc)

    loop(possibleWeights, Set.empty, 0).get
