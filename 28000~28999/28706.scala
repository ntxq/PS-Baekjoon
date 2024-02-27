import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    luckySeven(input.tail, Nil).mkString("\n")

  def luckySeven(input: List[String], acc: List[String]): List[String] =
    if input.isEmpty then acc.reverse
    else
      val n             = input.head.toInt
      val (turns, rest) = input.tail.splitAt(n)

      val dp = Array.fill(n, 7)(Option.empty[Boolean])

      def loop(turns: List[String], cur: Int, idx: Int): Boolean =
        turns match
          case Nil =>
            cur == 0
          case head :: tail =>
            dp(idx)(cur) match
              case Some(value) => value
              case None =>
                head.toCharArray.filter(_ != ' ') match
                  case Array('+', a, '+', b) =>
                    val ret = loop(tail, (cur + a.asDigit) % 7, idx + 1) || loop(tail, (cur + b.asDigit) % 7, idx + 1)
                    dp(idx)(cur) = Some(ret)
                    ret
                  case Array('+', a, '*', b) =>
                    val ret = loop(tail, (cur + a.asDigit) % 7, idx + 1) || loop(tail, (cur * b.asDigit) % 7, idx + 1)
                    dp(idx)(cur) = Some(ret)
                    ret
                  case Array('*', a, '+', b) =>
                    val ret = loop(tail, (cur * a.asDigit) % 7, idx + 1) || loop(tail, (cur + b.asDigit) % 7, idx + 1)
                    dp(idx)(cur) = Some(ret)
                    ret
                  case Array('*', a, '*', b) =>
                    val ret = loop(tail, (cur * a.asDigit) % 7, idx + 1) || loop(tail, (cur * b.asDigit) % 7, idx + 1)
                    dp(idx)(cur) = Some(ret)
                    ret
                  case _ =>
                    assert(false)

      luckySeven(rest, (if loop(turns, 1, 0) then "LUCKY" else "UNLUCKY") :: acc)
