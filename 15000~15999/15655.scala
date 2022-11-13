import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    val (bag, length) = inputBag()

    println(
      backtrack(Nil, bag, length).map(_.reverse.mkString(" ")).mkString("\n")
    )

  def backtrack(acc: List[Int], bag: List[Int], length: Int): List[List[Int]] =
    if length == 0 then acc :: Nil
    else
      bag match
        case Nil => Nil
        case h :: t =>
          backtrack(h :: acc, t, length - 1) ++ backtrack(acc, t, length)

  def inputBag(): (List[Int], Int) =
    val Array(bagLength, listLength) = readLine().split(" ").map(_.toInt)
    val bag = readLine().split(" ").map(_.toInt).toList.sorted
    (bag, listLength)
