import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    var line: Array[Int] = null
    while
      line = readLine().split(" ").map(_.toInt)
      line.length > 1
    do
      allLottery(line.tail)
      println

  def allLottery(candidates: Array[Int]): Unit =
    import util.chaining.scalaUtilChainingOps
    candidates.combinations(6).map(_.mkString(" ")).mkString("\n").pipe(println)
