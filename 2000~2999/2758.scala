import typings.node.{fsMod as fs}

object Main:
  def main(args: Array[String]): Unit =
    val input  = fs.readFileSync("/dev/stdin").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val dp = Array.fill(11, 2001)(0L)

    for j <- 0 to 2000
    do dp(0)(j) = 1

    for
      i <- 1 to 10
      j <- 1 to 2000
    do dp(i)(j) = dp(i)(j - 1) + dp(i - 1)(j / 2)

    def loop(input: List[String], acc: List[Long]): String =
      input match
        case Nil =>
          acc.reverse.mkString("\n")
        case x :: xs =>
          val Array(n, m) = x.split(" ").map(_.toInt)
          val ans         = dp(n)(m)
          loop(xs, ans :: acc)

    loop(input.tail, Nil)
