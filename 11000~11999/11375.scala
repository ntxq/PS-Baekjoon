import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, m) = readLine.split(' ').map(_.toInt)
    val adj = Array.fill(n)(readLine().split(' ').map(_.toInt - 1).tail)
    Matching(n, m, adj).maxMatching.pipe(println)

class Matching(n: Int, m: Int, adj: Array[Array[Int]]):
  val matches = Array.fill(m)(-1)
  val used = Array.fill(n)(false)

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

  final def maxMatching: Int =
    (0 until n).count(i =>
      (0 until n).foreach(j => used(j) = false)
      tryKuhn(i)
    )
