import typings.node.{fsMod as fs}

import scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val limit  = fs.readFileSync("/dev/stdin").toString.trim.toInt
    val result = List.range(1, limit + 1).map(countClap).sum.toString
    fs.writeFileSync("/dev/stdout", result + "\n")

  def countClap(n: Int): Int =
    n.toString.count(x => x == '3' || x == '6' || x == '9')
