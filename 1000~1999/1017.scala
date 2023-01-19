import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val numbers = readLine().split(' ').map(_.toInt)

    val (left, right) = numbers.partition(_ % 2 == numbers(0) % 2)
    val adj = Sieve.getAdj(left, right)
    val matches =
      if left.length != right.length then Array.emptyIntArray
      else BipartiteMatching(left.length, right.length, adj).getMatches

    if matches.isEmpty then println(-1)
    else matches.map(right(_)).sorted.mkString(" ").pipe(println)

object Sieve:
  val isPrime = Array.fill(2001)(true)
  isPrime(0) = false
  isPrime(1) = false

  for
    i <- 2 until 2001
    if isPrime(i)
  do
    for j <- i * i until 2001 by i
    do isPrime(j) = false

  def getAdj(odd: Array[Int], even: Array[Int]): Array[Array[Int]] =
    for i <- (odd.indices).toArray
    yield (0 until even.length).filter(j => isPrime(odd(i) + even(j))).toArray

class BipartiteMatching(n: Int, m: Int, adj: Array[Array[Int]]):
  val used = Array.ofDim[Boolean](n)
  val matches = Array.fill(m)(-1)

  private def tryKuhn(u: Int): Boolean =
    if used(u) || u == 0 then false
    else
      used(u) = true
      adj(u).exists(v =>
        if matches(v) == -1 || tryKuhn(matches(v)) then
          matches(v) = u
          true
        else false
      )

  def getMatches: Array[Int] =
    adj(0).filter(i =>
      matches.indices.foreach(matches(_) = -1)
      matches(i) = 0

      (1 until n).forall(u =>
        used.indices.foreach(used(_) = false)
        tryKuhn(u)
      )
    )
