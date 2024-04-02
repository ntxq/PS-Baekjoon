import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(s: Array[Boolean], t: Array[Boolean]): Option[Int] =
    val cnt =
      for
        i <- 1 until s.length
        if s(i - 1) != t(i - 1)
      yield
        s(i - 1) = !s(i - 1)
        s(i) = !s(i)
        if i + 1 < s.length then s(i + 1) = !s(i + 1)
        1

    if s.sameElements(t) then Some(cnt.sum) else None

  def solve(input: List[String]): String =
    input match
      case _ :: s :: t :: Nil =>
        val not_pressed = solve(s.toCharArray().map(_ == '1'), t.toCharArray().map(_ == '1'))

        val s_arr = s.toCharArray().map(_ == '1')
        val t_arr = t.toCharArray().map(_ == '1')
        s_arr(0) = !s_arr(0)
        s_arr(1) = !s_arr(1)
        val pressed = solve(s_arr, t_arr).map(_ + 1)

        ((not_pressed, pressed) match
          case (Some(x), Some(y)) => (x min y)
          case (Some(x), None)    => x
          case (None, Some(y))    => y
          case _                  => -1
        ).toString

      case _ =>
        assert(false)
