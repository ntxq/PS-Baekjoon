import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*
import scala.runtime.stdLibPatches.language.experimental.clauseInterleaving

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val n      = input.head.toInt
    val towers = input.tail.head.split(" ").map(_.toInt).toList.zipWithIndex

    val targets = Array.fill(n)(0)

    def loop(stack: List[(Int, Int)], towers: List[(Int, Int)]): String =
      towers match
        case Nil => targets.mkString(" ")
        case (h, i) :: ts =>
          val nStack = stack.dropWhile(_._1 < h)
          nStack.headOption match
            case Some((_, j)) =>
              targets(i) = j + 1
              loop((h, i) :: nStack, ts)
            case None =>
              loop((h, i) :: nStack, ts)

    loop(Nil, towers)
