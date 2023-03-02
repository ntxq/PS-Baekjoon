import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    val str = readLine().toList
    val env =
      (for ch <- ('A' to 'Z').take(n)
      yield ch -> readInt()).toMap


    def loop(eq: List[Char], stack: List[Double], env: Map[Char, Int]): Double =
      eq match
        case Nil => stack.head
        case '+' :: xs => loop(xs, stack.tail.head + stack.head :: stack.tail.tail, env)
        case '-' :: xs => loop(xs, stack.tail.head - stack.head :: stack.tail.tail, env)
        case '*' :: xs => loop(xs, stack.tail.head * stack.head :: stack.tail.tail, env)
        case '/' :: xs => loop(xs, stack.tail.head / stack.head :: stack.tail.tail, env)
        case ch :: xs => loop(xs, env(ch) :: stack, env)

    printf("%.2f\n", loop(str, Nil, env))
      
      
