import io.StdIn._
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val s = BigInt(readLine())

    @tailrec
    def loop(i: Int, acc: BigInt): Int =
      if acc - i < 0 then i - 1
      else loop(i + 1, acc - i)

    println(loop(1, s))
