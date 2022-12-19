import io.StdIn.*
import scala.annotation.tailrec
import scala.collection.Searching.Found
import scala.collection.Searching.InsertionPoint

object Main:
  def main(args: Array[String]): Unit =
    for
      _ <- 0 until readInt()
    do
      println(readLine().split(" ").map(_.reverse).mkString(" "))
