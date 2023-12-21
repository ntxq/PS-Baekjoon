import typings.node.{fsMod as fs}

import scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val dp = fibo(List(1, 1), 44).toVector

    val output =
      fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList match
        case _ :: months => months.map(x => dp(x.toInt)).mkString("\n")
        case Nil         => ""

    fs.writeFileSync("/dev/stdout", output + "\n")

  def fibo(acc: List[Int], n: Int): List[Int] =
    if n == 0 then acc.reverse
    else
      acc match
        case x :: y :: zs => fibo(x + y :: acc, n - 1)
        case _            => acc
