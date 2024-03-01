import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*
import scalajs.js.BigInt

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val n = BigInt(input.head)

    (for
      i <- 2 to 10
      base_n = n.toString(i)
      if base_n == base_n.reverse
    yield s"$i $base_n") match
      case IndexedSeq() => "NIE"
      case xs           => xs.mkString("\n")
