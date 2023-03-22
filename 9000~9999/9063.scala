object Main:
  def main(args: Array[String]): Unit =
    io.Source.stdin
      .getLines()
      .drop(1)
      .map(_.split(' ').map(_.toInt))
      .foldLeft((Int.MaxValue, Int.MinValue, Int.MaxValue, Int.MinValue)) {
        case ((minX, maxX, minY, maxY), Array(x, y)) =>
          (minX min x, maxX max x, minY min y, maxY max y)
      } match
      case (minX, maxX, minY, maxY) =>
        println((maxX - minX) * (maxY - minY))
