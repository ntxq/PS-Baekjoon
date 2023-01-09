import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val Array(s, t) = readLine().split(' ').map(_.toInt)

    import scala.collection.mutable.ArrayBuffer
    val adj = Array.fill(n)(ArrayBuffer.empty[Int])
    val m = readInt()
    for _ <- 0 until m do
      val Array(u, v) = readLine().split(' ').map(_.toInt)
      adj(u - 1) += v - 1
      adj(v - 1) += u - 1

    bfs(s - 1, t - 1, adj.map(_.toArray)).pipe(println)

  def bfs(s: Int, t: Int, adj: Array[Array[Int]]): Int =
    import scala.collection.mutable.Queue

    val queue = Queue.empty[Int]
    val dist = Array.fill(adj.size)(Int.MaxValue)

    queue.enqueue(s)
    dist(s) = 0

    while queue.nonEmpty do
      val u = queue.dequeue()
      for v <- adj(u) if dist(v) == Int.MaxValue do
        queue.enqueue(v)
        dist(v) = dist(u) + 1

    if dist(t) == Int.MaxValue then -1 else dist(t)
