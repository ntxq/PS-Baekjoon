import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    val (length, bag) = getInput()
    println(
      backtrack(bag, Nil, length).map(_.reverse.mkString(" ")).mkString("\n")
    )

  def getInput(): (Int, List[Int]) =
    val Array(bagLength, listLength) = readLine().split(" ").map(_.toInt)
    val bag = readLine().split(" ").map(_.toInt).sorted.toList
    (listLength, bag)

  def backtrack(bag: List[Int], acc: List[Int], length: Int): List[List[Int]] =
    if length == 0 then acc :: Nil
    else bag.flatMap(item => backtrack(bag, item :: acc, length - 1))
