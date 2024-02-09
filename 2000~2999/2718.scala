import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val t = input.head.toInt

    val dp = Array.fill(25, 1 << 4)(0)
    def countTiles(curLen: Int, curState: Int): Int =
      if curLen < 0
      then 0
      else if curLen == 0
      then if curState == 0 then 1 else 0
      else if dp(curLen)(curState) != 0
      then dp(curLen)(curState)
      else
        dp(curLen)(curState) = curState match
          case 0 =>
            countTiles(curLen - 1, 0) + countTiles(curLen - 2, 0) + countTiles(curLen - 1, 3)
              + countTiles(curLen - 1, 9) + countTiles(curLen - 1, 12)
          case 3 =>
            countTiles(curLen - 1, 0) + countTiles(curLen - 1, 12)
          case 6 =>
            countTiles(curLen - 1, 9)
          case 9 =>
            countTiles(curLen - 1, 0) + countTiles(curLen - 1, 6)
          case 12 =>
            countTiles(curLen - 1, 0) + countTiles(curLen - 1, 3)
        dp(curLen)(curState)

    (for i <- input.tail.map(_.toInt)
    yield countTiles(i, 0).toString).mkString("\n")
