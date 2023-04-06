object Main:
  def main(args: Array[String]): Unit =
    println(
      io.Source.stdin
        .getLines()
        .drop(1)
        .foldLeft[Set[String]](Set.empty)((acc, line) =>
          line.split(' ') match
            case Array(name, "enter") => acc + name
            case Array(name, "leave") => acc - name
        )
        .toList
        .sorted
        .reverse
        .mkString("\n")
    )
