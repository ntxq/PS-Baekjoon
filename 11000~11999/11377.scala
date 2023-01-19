import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m, k) = readLine.split(' ').map(_.toInt)
    val adj =
      for _ <- (0 until n).toArray
      yield readLine().split(' ').map(_.toInt - 1).tail

    val single = BipartiteMatching(n, m, adj).count
    val double = BipartiteMatching(2 * n, m, adj ++ adj).count

    println(
      (single + k) min double
    )

class BipartiteMatching(n: Int, m: Int, adj: Array[Array[Int]]):
  val used = Array.ofDim[Boolean](n)
  val matches = Array.fill(m)(-1)

  private def tryKuhn(u: Int): Boolean =
    if used(u) then false
    else
      used(u) = true
      adj(u).exists(v =>
        if matches(v) == -1 || tryKuhn(matches(v)) then
          matches(v) = u
          true
        else false
      )

  final def count: Int =
    (0 until n).count(i =>
      used.indices.foreach(j => used(j) = false)
      tryKuhn(i)
    )
