import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val Array(q, m) = input.head.split(" ").map(_.toInt)
    val ops         = input.tail.map(_.split(" ").map(_.toInt))

    val modPos = Array.fill(m)(collection.mutable.Stack.empty[Int])
    val nums   = collection.mutable.Stack.empty[Int]

    val ans = collection.mutable.StringBuilder.newBuilder
    for op <- input.tail
    do
      op.split(" ").map(_.toInt) match
        case Array(1, x) =>
          val modded = x % m
          modPos(modded).push(nums.size)
          nums.push(modded)

        case Array(2) =>
          if nums.nonEmpty
          then modPos(nums.pop()).pop()

        case Array(3) =>
          modPos.foldLeft(Option(nums.size)) { (acc, s) =>
            for
              x <- acc
              y <- s.headOption
            yield x min y
          } match
            case None         => ans ++= "-1\n"
            case Some(minPos) => ans ++= s"${nums.size - minPos}\n"

    ans.mkString
