object Main:
  def main(args: Array[String]): Unit =
    val Array(str, base) = io.StdIn.readLine().split(' ')
    val baseN = base.toInt

    println(str.foldLeft(0) { (acc, c) =>
      if '0' <= c && c <= '9' then acc * baseN + c.asDigit
      else acc * baseN + c - 'A' + 10
    })
