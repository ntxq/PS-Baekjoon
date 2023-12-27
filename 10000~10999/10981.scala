import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.map(_.split(" "))
    val output = getFinalists(input.toList).mkString("\n")
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def getFinalists(input: List[Array[String]]): List[String] =
    input match
      case Array(_, k) :: teams =>
        val scores =
          for case Array(uni, name, score, penalty) <- teams
          yield (uni, name, score.toInt, penalty.toInt)

        val sortedScores = scores.sortWith { case ((_, _, a1, b1), (_, _, a2, b2)) => a1 > a2 || a1 == a2 && b1 < b2 }

        def getTopK(teams: List[(String, String)], k: Int, acc: List[String], unis: Set[String]): List[String] =
          if k == 0
          then acc
          else
            teams match
              case (uni, name) :: xs =>
                if unis.contains(uni) then getTopK(xs, k, acc, unis) else getTopK(xs, k - 1, name :: acc, unis + uni)
              case Nil => acc
        getTopK(sortedScores.map(team => (team._1, team._2)), k.toInt, Nil, Set.empty).reverse

      case _ => Nil
