import io.StdIn.*
import scala.annotation.tailrec
import scala.collection.Searching.Found
import scala.collection.Searching.InsertionPoint

object Main:
  def main(args: Array[String]): Unit =
    fourPrimeSum(readInt())

  def fourPrimeSum(target: Int): Unit =
    if target < 8 then println("-1")
    else
      val sieve = Array.ofDim[Boolean](target)
      val primes =
        for
          i <- 2 until target
          if !sieve(i)
        yield
          for j <- i.toLong * i until target by i
          do sieve(j.toInt) = true
          i

      val goldbachTarget =
        if target % 2 == 0 then
          print("2 2 ")
          target - 4
        else
          print("2 3 ")
          target - 5

      primes.find(x =>
        primes.search(goldbachTarget - x) match
          case Found(foundIndex) =>
            println(s"$x ${primes(foundIndex)}")
            true
          case InsertionPoint(insertionPoint) => false
      )
