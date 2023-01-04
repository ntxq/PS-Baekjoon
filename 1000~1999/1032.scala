import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val targets =
      for _ <- 0 until readInt()
      yield readLine()
    println(getPattern(targets))

  def getPattern(targets: Seq[String]): String =
    (for
      i <- 0 until targets.head.length
      constant = targets.head.charAt(i)
      isMatch = targets.forall(_.charAt(i) == constant)
    yield if isMatch then constant else '?').mkString
