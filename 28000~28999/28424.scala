import typings.node.{fsMod as fs}

import scala.scalajs.js.Math
import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = loyaltyGame(input).mkString("\n")
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def parseParams(input: List[String]): (Array[Int], List[String]) =
    input match
      case Nil => (Array(), Nil)
      case params :: rest =>
        val Array(n, _)         = params.split(" ").map(_.toInt)
        val (students, queries) = rest.splitAt(n)
        (students.map(_.toInt).toArray, queries)

  def loyaltyGame(input: List[String]): List[String] =
    val (students, queries) = parseParams(input)
    val drank               = Array.fill(students.length)(0)

    val parents = Array.range(0, students.length)

    def findSet(v: Int): Int =
      if parents(v) == v then v
      else
        parents(v) = findSet(parents(v))
        parents(v)

    def unionSets(a: Int, b: Int): Unit =
      if b < students.length
      then
        val x = findSet(a)
        val y = findSet(b)
        parents(x) = y

    def drink(i: Int, x: Int): Unit =
      if i < students.length
      then
        val j       = findSet(i)
        val toDrink = x min (students(j) - drank(j))
        drank(j) += toDrink

        if toDrink < x
        then
          unionSets(j, j + 1)
          drink(j + 1, x - toDrink)

    def loop(queries: List[String], acc: List[String]): List[String] =
      queries match
        case Nil => acc.reverse
        case q :: qs =>
          q.split(" ").map(_.toInt) match
            case Array(1, i, x) =>
              drink(i - 1, x)
              loop(qs, acc)

            case Array(2, i) =>
              val ans = drank(i - 1).toString
              loop(qs, ans :: acc)

            case _ =>
              acc.reverse

    loop(queries, Nil)
