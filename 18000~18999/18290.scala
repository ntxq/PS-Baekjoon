import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    val (board, k) = readBoard()
    println(backtrack(board, k))

  def readBoard(): (Array[Array[Int]], Int) =
    val Array(n, m, k) = readLine().split(" ").map(_.toInt)
    val board =
      for _ <- 0 until n yield readLine().split(" ").map(_.toInt)
    (board.toArray, k)

  def backtrack(board: Array[Array[Int]], k: Int): Int =
    val visited =
      Array.fill(board.length)(Array.fill(board(0).length)(false))

    def loop(idx: Int, count: Int, acc: Int): Int =
      if count == k then acc
      else if idx == board.length * board(0).length then -10000 * k
      else
        val (i, j) = (idx / board(0).length, idx % board(0).length)
        if (i == 0 || !visited(i - 1)(j))
          && (i == board.length - 1 || !visited(i + 1)(j))
          && (j == 0 || !visited(i)(j - 1))
          && (j == board(0).length - 1 || !visited(i)(j + 1))
        then
          visited(i)(j) = true
          val withAcc = loop(idx + 1, count + 1, acc + board(i)(j))
          visited(i)(j) = false
          val withoutAcc = loop(idx + 1, count, acc)
          withAcc max withoutAcc
        else loop(idx + 1, count, acc)

    loop(0, 0, 0)
