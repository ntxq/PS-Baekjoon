import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    readLine().pipe(firstPartition).pipe(println)

  def allPartitions(s: String): Seq[String] =
    for
      i <- 1 to s.length - 2
      j <- i + 1 to s.length - 1
    yield s.substring(0, i).reverse
      + s.substring(i, j).reverse
      + s.substring(j).reverse

  def firstPartition(s: String): String =
    allPartitions(s).min
