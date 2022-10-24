import io.StdIn._
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val input = 
      for 
        _ <- 0 until 5
      yield
        readInt()
    println(input.sum / 5)
    println(input.sorted.apply(2))
