import io.StdIn.*
import scala.annotation.tailrec
import collection.mutable

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, k) = readLine().split(" ").map(_.toInt)
    val belt = readLine().split(" ").map(_.toInt).to(mutable.ArrayDeque)
    val converyor = Converyor(n, k, belt)
    println(converyor.run())

class Converyor(length: Int, limit: Int, belt: mutable.ArrayDeque[Int]):
  private val robots = mutable.ArrayDeque.fill(length)(false)
  private var expired = 0

  private def rotateOnce(): Unit =
    belt.prepend(belt.removeLast())
    robots.prepend(robots.removeLast())
    robots(length - 1) = false

  private def moveRobots(): Unit =
    for
      i <- length - 2 to 0 by -1
      if robots(i) && belt(i + 1) > 0 && !robots(i + 1)
    do
      robots(i) = false
      robots(i + 1) = true
      belt(i + 1) -= 1
      if belt(i + 1) == 0 then expired += 1
    robots(length - 1) = false

  private def putRobot(): Unit =
    if belt(0) > 0 then
      robots(0) = true
      belt(0) -= 1
      if belt(0) == 0 then expired += 1

  @tailrec
  final def run(count: Int = 1): Int =
    rotateOnce()
    moveRobots()
    putRobot()
    if expired >= limit then count
    else run(count + 1)
