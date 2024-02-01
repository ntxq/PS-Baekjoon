import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val Array(n, m) = input.head.split(" ").map(_.toLong)

    val cache = scala.collection.mutable.Map.empty[Long, Boolean]
    def loop(x: Long): Boolean =
      if x == m
      then true
      else if x < m
      then false
      else if cache.contains(x)
      then cache(x)
      else
        cache(x) = loop(x / 2) || loop(x - x / 2)
        cache(x)

    if loop(n) then "YES" else "NO"
