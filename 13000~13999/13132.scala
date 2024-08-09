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
    val Array(n, m, b) = input.head.split(" ").map(_.toInt)

    val mPercent           = m / 100.0
    val mPercentComplement = 1 - mPercent

    def loop(games: List[Array[Double]], money: Double): Double =
      if money <= b then 0
      else
        games match
          case Array(p, r) :: next =>
            val winMoney  = money * mPercent * r + money * mPercentComplement
            val loseMoney = money * mPercentComplement

            val pPercent = p / 100.0
            loop(next, winMoney) * pPercent + loop(next, loseMoney) * (1 - pPercent)

          case _ => if money > 100 then 100 else 0

    "%.4f".format(loop(input.tail.map(_.split(" ").map(_.toDouble)), 100).toDouble)
