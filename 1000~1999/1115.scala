import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*
import scala.collection.mutable

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = countCycles(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def countCycles(input: List[String]): Int =
    val graph   = input.tail.head.split(" ").map(_.toInt).toArray
    val visited = Array.fill(graph.length)(false)

    def visit(idx: Int): Unit =
      if !visited(idx)
      then
        visited(idx) = true
        visit(graph(idx))

    def loop(idx: Int, acc: Int): Int =
      if idx == graph.length
      then acc
      else if visited(idx)
      then loop(idx + 1, acc)
      else
        visit(idx)
        loop(idx + 1, acc + 1)

    val count = loop(0, 0)
    if count > 1
    then count
    else 0
