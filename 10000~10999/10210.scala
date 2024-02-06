import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def visit(soldier: String, visited: Array[Array[Boolean]]): Unit =
    def loop(x: Int, y: Int, soldier: List[Char]): Unit =
      soldier match
        case Nil => ()
        case 'u' :: rest =>
          visited(x + 1)(y) = true
          loop(x + 1, y, rest)
        case 'd' :: rest =>
          visited(x - 1)(y) = true
          loop(x - 1, y, rest)
        case 'l' :: rest =>
          visited(x)(y - 1) = true
          loop(x, y - 1, rest)
        case 'r' :: rest =>
          visited(x)(y + 1) = true
          loop(x, y + 1, rest)
        case _ => ()

    visited(0)(0) = true
    loop(0, 0, soldier.toList)

  def findCavity(s: Int, visited: Array[Array[Boolean]]): Int =
    def checkSize(x: Int, y: Int): Int =
      if x < 0 || x >= visited.length || y < 0 || y >= visited(0).length || visited(x)(y) then 0
      else
        visited(x)(y) = true
        1 + checkSize(x - 1, y) + checkSize(x + 1, y) + checkSize(x, y - 1) + checkSize(x, y + 1)

    (for
      sx <- 0 until visited.length
      sy <- 0 until visited(0).length
      if !visited(sx)(sy)
      if checkSize(sx, sy) >= s
    yield true).size

  def solve(input: List[String]): String =
    val k = input.head.toInt

    val outputBuilder = scala.collection.mutable.StringBuilder()
    def loop(dataSetIdx: Int, input: List[String]): Unit =
      if dataSetIdx < k
      then
        val Array(h, w, s, n) = input.head.split(" ").map(_.toInt)
        val (soldiers, rest)  = input.tail.splitAt(n)

        val visited = Array.fill(h, w)(false)
        soldiers.foreach(visit(_, visited))

        val result = findCavity(s, visited)
        outputBuilder ++= s"Data Set ${dataSetIdx + 1}:\n$result\n\n"

        loop(dataSetIdx + 1, rest)

    loop(0, input.tail)
    outputBuilder.toString
