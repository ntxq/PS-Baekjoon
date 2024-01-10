import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*
import scala.collection.mutable

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = visitBuilding(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def parseInput(input: List[String]): (Int, Array[mutable.ArrayBuffer[Int]]) =
    input.map(_.split(" ").map(_.toInt)) match
      case Array(n, h, _) :: rest =>
        val toVisit = Array.fill(h)(mutable.ArrayBuffer.empty[Int])
        for case Array(i, j) <- rest
        do toVisit(i - 1).append(j - 1)

        for i <- 0 until h
        do toVisit(i).sortInPlace()
        (n, toVisit)

      case _ => (0, Array.empty)

  def visitBuilding(input: List[String]): Int =
    val (n, toVisit) = parseInput(input)

    def visit(floor: Int, lIdx: Int, rIdx: Int, lAcc: Int, rAcc: Int, todo: Int): Int =
      if todo == 0
      then (lAcc min rAcc) - 100
      else if toVisit(floor).isEmpty
      then visit(floor + 1, lIdx, rIdx, lAcc + 100, rAcc + 100, todo)
      else
        val s = toVisit(floor).head
        val e = toVisit(floor).last

        val lToL = (s - lIdx).abs + (e - s)
        val lToR = (e - lIdx).abs + (e - s)
        val rToL = (s - rIdx).abs + (e - s)
        val rToR = (e - rIdx).abs + (e - s)

        val newLAcc = ((lToR + lAcc) min (rToR + rAcc)) + 100
        val newRAcc = ((lToL + lAcc) min (rToL + rAcc)) + 100
        visit(floor + 1, s, e, newLAcc, newRAcc, todo - toVisit(floor).size)

    visit(0, 0, 0, 0, 0, n)
