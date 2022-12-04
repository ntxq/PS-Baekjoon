import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    readInt().pipe(bfs).pipe(println)

  def bfs(target: Int): Int =
    case class State(value: Int, clip: Int, dist: Int)

    val dist = Array.fill(target * 2 + 1, target * 2 + 1)(Int.MaxValue)
    val q = mutable.Queue.empty[State]

    q.enqueue(State(1, 0, 0))
    var minDist = 0

    while minDist == 0 do
      val State(value, clip, curDist) = q.dequeue()

      if value == target then minDist = curDist

      if curDist + 1 < dist(value)(value) then
        dist(value)(value) = curDist + 1
        q.enqueue(State(value, value, curDist + 1))

      if value + clip <= target * 2 && curDist + 1 < dist(value + clip)(clip)
      then
        dist(value + clip)(clip) = curDist + 1
        q.enqueue(State(value + clip, clip, curDist + 1))

      if value > 0 && curDist + 1 < dist(value - 1)(clip) then
        dist(value - 1)(clip) = curDist + 1
        q.enqueue(State(value - 1, clip, curDist + 1))

    minDist
