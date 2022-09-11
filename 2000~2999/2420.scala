import java.util.Scanner

object Main:
  def main(args: Array[String]): Unit =
    val sc = Scanner(System.in)
    val N = sc.nextLong()
    val M = sc.nextLong()
    println((N - M).abs)
