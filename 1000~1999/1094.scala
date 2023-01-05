import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    readInt().pipe(_.toBinaryString).pipe(_.count(_ == '1')).pipe(println)