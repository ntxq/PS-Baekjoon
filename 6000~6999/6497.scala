import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

case class Edge(s: Int, t: Int, w: Int)

object Main:
  def main(args: Array[String]): Unit =
    (for Array(m, n) <- LazyList
        .continually(readLine().split(' ').map(_.toInt))
        .takeWhile {
          case Array(0, 0) => false
          case _           => true
        }
    yield (for _ <- 0 until n
    yield readLine().split(' ').map(_.toInt).pipe { case Array(s, t, w) =>
      Edge(s, t, w)
    }).pipe(edges => edges.map(_.w).sum - kruskalMST(m, edges)))
      .mkString("\n")
      .pipe(println)

  private def kruskalMST(n: Int, edges: IndexedSeq[Edge]): Int =
    val parents = Array.range(0, n)
    val ranks = Array.fill(n)(0)

    def findSet(x: Int): Int =
      if parents(x) == x then x
      else
        parents(x) = findSet(parents(x))
        parents(x)
    def unionSets(x: Int, y: Int): Unit =
      val xRoot = findSet(x)
      val yRoot = findSet(y)
      if xRoot == yRoot then ()
      else if ranks(xRoot) < ranks(yRoot) then parents(xRoot) = yRoot
      else if ranks(xRoot) > ranks(yRoot) then parents(yRoot) = xRoot
      else
        parents(yRoot) = xRoot
        ranks(xRoot) += 1

    edges
      .sortBy(_.w)
      .foldLeft(0) { case (acc, Edge(s, t, w)) =>
        if findSet(s) == findSet(t) then acc
        else
          unionSets(s, t)
          acc + w
      }
