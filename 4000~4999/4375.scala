import io.StdIn.*
import collection.mutable
import scala.annotation.tailrec
import java.util.Scanner
import java.io.PrintWriter
import java.io.BufferedOutputStream

object Main:
  def main(args: Array[String]): Unit =
    val scanner = Scanner(System.in)
    val out = PrintWriter(BufferedOutputStream(System.out))

    while scanner.hasNextLine() do
      val line = scanner.nextLine()
      val digits = findOneMultiple(line.toInt)
      out.println(digits)
    out.flush()

  def findOneMultiple(n: Int): Int =
    lazy val numbers: LazyList[Int] =
      (1 % n) #:: numbers.map(x => (x * 10 + 1) % n)
    numbers.indexOf(0) + 1
