import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

/*
Subproblem:
  dp[k][a][b][c] = String with K pairs with a,b,c number of A,B,C
Recurrence:
  dp[k][a][b][c] = dp[k][a-1][b][c] + 'A'
  dp[k][a][b][c] = dp[k-a][a][b-1][c] + 'B'
  dp[k][a][b][c] = dp[k-a-b][a][b][c-1] + 'C'
Topology:
  k -> a -> b -> c
 */

object Main:
  def main(args: Array[String]): Unit =
    val Array(n, k) = readLine().split(' ').map(_.toInt)
    val result = solve(n, k)
    if !result then println(-1)

  def solve(n: Int, k: Int): Boolean =
    val dp = Array.fill(k + 1, n + 1, n + 1, n + 1)(' ')
    dp(0)(1)(0)(0) = 'A'
    dp(0)(0)(1)(0) = 'B'
    dp(0)(0)(0)(1) = 'C'

    @tailrec
    def printLoop(i: Int, j: Int, l: Int, m: Int, acc: List[Char]): Unit =
      if j == 0 && l == 0 && m == 0 then println(acc.mkString)
      else
        dp(i)(j)(l)(m) match
          case 'A' => printLoop(i, j - 1, l, m, 'A' :: acc)
          case 'B' => printLoop(i - j, j, l - 1, m, 'B' :: acc)
          case 'C' => printLoop(i - j - l, j, l, m - 1, 'C' :: acc)

    @tailrec
    def loop(i: Int, j: Int, l: Int, m: Int): Boolean =
      if i > k then false
      else if j == n then loop(i + 1, 0, l, m)
      else if l == n then loop(i, j + 1, 0, m)
      else if m == n then loop(i, j, l + 1, 0)
      else if dp(i)(j)(l)(m) == ' ' then loop(i, j, l, m + 1)
      else
        dp(i)(j + 1)(l)(m) = 'A'
        if i == k && j + l + m + 1 == n then
          printLoop(i, j, l, m, 'A' :: Nil)
          return true

        if i + j <= k then
          dp(i + j)(j)(l + 1)(m) = 'B'
          if i + j == k && j + l + m + 1 == n then
            printLoop(i, j, l, m, 'B' :: Nil)
            return true

        if i + j + l <= k then
          dp(i + j + l)(j)(l)(m + 1) = 'C'
          if i + j + l == k && j + l + m + 1 == n then
            printLoop(i, j, l, m, 'C' :: Nil)
            return true

        loop(i, j, l, m + 1)

    loop(0, 0, 0, 0)
