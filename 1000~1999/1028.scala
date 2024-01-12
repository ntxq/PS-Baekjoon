import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*
import scala.collection.mutable

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = countDiamond(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def countDiamond(input: List[String]): Int =
    val board = input.tail.map(_.toCharArray).toArray

    val ld = Array.fill(board.length, board(0).length)(0)
    val rd = Array.fill(board.length, board(0).length)(0)
    val lu = Array.fill(board.length, board(0).length)(0)
    val ru = Array.fill(board.length, board(0).length)(0)

    for
      i <- board.length - 1 to 0 by -1
      j <- board(0).indices
    do
      if board(i)(j) == '1'
      then
        ld(i)(j) = 1 + (if i + 1 < board.length && j - 1 >= 0 then ld(i + 1)(j - 1) else 0)
        rd(i)(j) = 1 + (if i + 1 < board.length && j + 1 < board(0).length then rd(i + 1)(j + 1) else 0)

    for
      i <- board.indices
      j <- board(0).indices
    do
      if board(i)(j) == '1'
      then
        lu(i)(j) = 1 + (if i - 1 >= 0 && j - 1 >= 0 then lu(i - 1)(j - 1) else 0)
        ru(i)(j) = 1 + (if i - 1 >= 0 && j + 1 < board(0).length then ru(i - 1)(j + 1) else 0)

    def loop(i: Int, j: Int, acc: Int): Int =
      if i >= board.length
      then acc
      else if j >= board(0).length
      then loop(i + 1, 0, acc)
      else if board(i)(j) == '0'
      then loop(i, j + 1, acc)
      else
        val curMax = (for
          k <- (acc + 1) to (ld(i)(j) min rd(i)(j))
          bi = i + 2 * (k - 1)
          if bi < board.length
          if lu(bi)(j) >= k && ru(bi)(j) >= k
        yield k).maxOption.getOrElse(0)

        loop(i, j + 1, curMax max acc)

    loop(0, 0, 0)
