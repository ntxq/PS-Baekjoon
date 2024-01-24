import typings.node.{fsMod as fs}

import scala.scalajs.js.annotation.*

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = bubbleSort(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def bubbleSort(input: List[String]): String =
    val Array(n, k) = input.head.split(" ").map(_.toInt)
    val numbers     = input.tail.head.split(" ").map(_.toInt)

    val queue = scala.collection.mutable.PriorityQueue.empty[Int].reverse
    for i <- 0 until k
    do queue.enqueue(numbers(i))

    for i <- 0 until (n - k)
    do
      queue.enqueue(numbers(i + k))
      numbers(i) = queue.dequeue()

    for i <- (n - k) until n
    do numbers(i) = queue.dequeue()

    numbers.mkString(" ")
