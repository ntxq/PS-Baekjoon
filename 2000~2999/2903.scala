object Main:
  def main(args: Array[String]): Unit =
    val n = io.StdIn.readInt()
    
    val base = (0 until n).foldLeft(1)((acc, _) => acc * 2) + 1
    println(base * base)