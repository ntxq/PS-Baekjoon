import typings.node.{fsMod as fs}

import scalajs.js.annotation.*
import scala.scalajs.js.Math

object Main:
  def main(args: Array[String]): Unit =
    val input = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList.tail
    val output = areaBetween(input, Nil)
    fs.writeFileSync("/dev/stdout", output + "\n")

  def degBetween(from: (Int, Int, Int, Int), to: (Int, Int, Int, Int)): Double =
    val (sh, sm, ss, sss) = from
    val (eh, em, es, ess) = to

    val s = (sh * 60 * 60 * 100) + (sm * 60 * 100) + (ss * 100) + sss
    val e = (eh * 60 * 60 * 100) + (em * 60 * 100) + (es * 100) + ess

    (if e <= s
     then (e + 12 * 60 * 60 * 100 - s)
     else (e - s)) * (360.0 / 12 / 60 / 60 / 100)

  def areaBetween(query: List[String], acc: List[String]): String =
    query match
      case from :: to :: radius :: rest =>
        val s = from.split(" ").map(_.toInt) match
          case Array(h, m, s, ss) => (h, m, s, ss)
        val e = to.split(" ").map(_.toInt) match
          case Array(h, m, s, ss) => (h, m, s, ss)

        val area = Math.PI * Math.pow(radius.toDouble, 2) * degBetween(s, e) / 360.0
        areaBetween(rest, f"${acc.length + 1}. ${area}%.3f" :: acc)

      case _ => acc.reverse.mkString("\n")
