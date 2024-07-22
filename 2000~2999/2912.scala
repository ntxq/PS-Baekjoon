import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*
import scala.collection.Searching.Found
import scala.collection.Searching.InsertionPoint

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val Array(n, m) = input(0).split(" ").map(_.toInt)
    val nums        = input(1).split(" ").map(_.toInt)

    val counts = Array.fill(m + 1)(Vector.empty[Int])
    for (nums, idx) <- nums.zipWithIndex
    do counts(nums) = counts(nums) :+ idx

    def loop(l: Int, r: Int, k: Int, idx: Int): String =
      if idx > 50
      then "no"
      else
        val cnt = counts(k).search(r + 1).insertionPoint - counts(k).search(l).insertionPoint
        if cnt > (r - l + 1) / 2
        then s"yes $k"
        else loop(l, r, nums(scala.util.Random.between(l, r + 1)), idx + 1)

    (for Array(l, r) <- input.drop(3).map(_.split(" ").map(_.toInt))
    yield loop(l - 1, r - 1, nums(scala.util.Random.between(l - 1, r)), 0)).mkString("\n")
