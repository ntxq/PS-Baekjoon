import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    val a = readLine()
    val b = readLine()
    println(if binaryGame(a, b) then "VICTORY" else "DEFEAT")

  def binaryGame(from: String, to: String): Boolean =
    val fromOnes = from.count(_ == '1')
    val toOnes = to.count(_ == '1')

    if fromOnes >= toOnes then true
    else if fromOnes % 2 == 1 && fromOnes + 1 == toOnes then true
    else false
