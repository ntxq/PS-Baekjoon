import scala.scalajs.js

import js.Dynamic.global
import js.DynamicImplicits.*

object Main:
  def main(args: Array[String]): Unit =
    val fs     = global.require("fs")
    val input  = fs.readFileSync(0, "utf-8").toString.trim.linesIterator.toList
    val output = solve(input)
    fs.writeFileSync("/dev/stdout", s"$output\n")

  def solve(input: List[String]): String =
    val adj = Array.fill(input.head.length)(List.empty[Int])

    def loop(idx: Int, input: List[Char], cont: (Int, List[Char]) => Unit): Unit =
      input match
        case '0' :: tail =>
          cont(idx + 1, tail)
        case '1' :: tail =>
          adj(idx) = List(idx + 1)
          loop(idx + 1, tail, cont)
        case '2' :: tail =>
          adj(idx) = List(idx + 1)
          loop(
            idx + 1,
            tail,
            (nIdx, nTail) =>
              adj(idx) = nIdx :: adj(idx)
              loop(nIdx, nTail, cont)
          )
        case _ => ()

    loop(0, input.head.toList, (_, _) => ())

    // dp(i)(j) = i-th node, (r,g,b)-color
    val maxDP = Array.fill(adj.length, 3)(0)
    val minDP = Array.fill(adj.length, 3)(0)

    for
      i <- adj.length - 1 to 0 by -1
      j <- 0 until 3
    do
      adj(i) match
        case Nil =>
          maxDP(i)(j) = (if j == 1 then 1 else 0)
          minDP(i)(j) = (if j == 1 then 1 else 0)
        case List(x) =>
          maxDP(i)(j) = (if j == 1 then 1 else 0) + (0 until 3).filter(_ != j).map(maxDP(x)).max
          minDP(i)(j) = (if j == 1 then 1 else 0) + (0 until 3).filter(_ != j).map(minDP(x)).min
        case List(x, y) =>
          val (a, b) = (0 until 3).filter(_ != j) match
            case IndexedSeq(a, b) => (a, b)
          maxDP(i)(j) = (if j == 1 then 1 else 0) + ((maxDP(x)(a) + maxDP(y)(b)) max (maxDP(x)(b) + maxDP(y)(a)))
          minDP(i)(j) = (if j == 1 then 1 else 0) + ((minDP(x)(a) + minDP(y)(b)) min (minDP(x)(b) + minDP(y)(a)))
        case _ =>
          ()

    s"${maxDP(0).max} ${minDP(0).min}"
