import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*
import scalajs.js.BigInt
import typings.std.stdStrings.done

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val stack = scala.collection.mutable.Stack.empty[(Int, Int)]
    def loop(idx: Int, nums: List[Int], acc: List[Int]): List[Int] =
      (nums, stack.headOption) match
        case (Nil, _) => acc.reverse
        case (x :: xs, None) =>
          stack.push((idx, x))
          loop(idx + 1, xs, 0 :: acc)
        case (x :: xs, Some(idx_y, y)) =>
          if y < x
          then
            stack.push((idx, x))
            loop(idx + 1, xs, idx_y :: acc)
          else
            stack.pop()
            loop(idx, x :: xs, acc)

    loop(1, input.tail.head.split(" ").map(_.toInt).toList, Nil).mkString(" ")
