import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList.tail.head
    val output = countWhistle(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def countWhistle(input: String): Int =
    val dp = Array.fill(200000)(0L)

    dp(0) = 1
    for i <- 1 until 200000
    do dp(i) = (2 * dp(i - 1)) % 1000000007

    def loop(input: List[Char], eCnt: Int, toAdd: Int, acc: Int): Int =
      input match
        case Nil         => acc
        case 'W' :: rest => loop(rest, eCnt, toAdd, (acc + toAdd) % 1000000007)
        case 'H' :: rest => loop(rest, eCnt, (toAdd + dp(eCnt).toInt - eCnt - 1) % 1000000007, acc)
        case 'E' :: rest => loop(rest, eCnt + 1, toAdd, acc)
        case _ :: rest   => loop(rest, eCnt, toAdd, acc)

    loop(input.toList.reverse, 0, 0, 0)
