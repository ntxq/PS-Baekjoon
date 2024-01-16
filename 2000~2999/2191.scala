import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList.map(_.split(" "))
    val output = countMouse(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def parseInput(input: List[Array[String]]): ((Int, Int, Int, Int), Array[(Long, Long)], Array[(Long, Long)]) =
    val params = input.head.map(_.toInt) match
      case Array(n, m, s, v) => (n, m, s, v)
      case _                 => assert(false)
    val locs = input.tail.map(_.map(_.toDouble).map(_ * 1000).map(_.round)).map {
      case Array(x, y) => (x, y)
      case _           => assert(false)
    }
    val (mice, holes) = locs.splitAt(params._1)
    (params, mice.toArray, holes.toArray)

  def countMouse(input: List[Array[String]]): Int =
    val ((n, m, s, v), mice, holes) = parseInput(input)

    val maxDist = s.toLong * v * s * v * 1000 * 1000
    val adj =
      for i <- mice.indices.toArray
      yield for
        j <- holes.indices.toArray
        dx   = (mice(i)._1 - holes(j)._1).abs
        dy   = (mice(i)._2 - holes(j)._2).abs
        dist = dx * dx + dy * dy
        if dist <= maxDist
      yield j

    val matched = Array.fill(n)(-1)
    val used    = Array.fill(n)(false)

    def try_kuhn(u: Int): Boolean =
      if used(u)
      then false
      else
        used(u) = true

        def loop(idx: Int): Boolean =
          if idx >= adj(u).length
          then false
          else
            val v = adj(u)(idx)
            if matched(v) == -1 || try_kuhn(matched(v))
            then
              matched(v) = u
              true
            else loop(idx + 1)
        loop(0)

    for i <- mice.indices
    do
      used.indices.foreach(used(_) = false)
      try_kuhn(i)

    n - matched.count(_ != -1)
