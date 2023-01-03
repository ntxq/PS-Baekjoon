import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val f = readInt()
    printf("%02d\n", solve(n, f))

  def solve(n: Int, f: Int) =
    val offset = (n - n % 100) % f
    if offset == 0 then 0
    else f - offset
