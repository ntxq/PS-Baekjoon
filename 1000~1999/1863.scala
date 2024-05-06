import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val stack = scala.collection.mutable.Stack[Int]()
    def loop(skyline: List[Int], cnt: Int): Int =
      skyline match
        case Nil => cnt
        case h :: hs =>
          if h == 0 then
            stack.clear()
            loop(hs, cnt)
          else if stack.isEmpty || stack.top < h then
            stack.push(h)
            loop(hs, cnt + 1)
          else if stack.top > h then
            stack.pop()
            loop(skyline, cnt)
          else loop(hs, cnt)

    val skyline = input.tail.map(_.split(" ").map(_.toInt)).map { case Array(x, y) => (x, y) }.sortBy(_._1).map(_._2)
    loop(skyline, 0).toString
