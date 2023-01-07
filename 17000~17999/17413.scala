import io.StdIn.*
import scala.annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    readLine().pipe(reverseTagged).pipe(println)

  def reverseTagged(input: String): String =
    import scala.collection.mutable.{StringBuilder, ListBuffer}

    val sb = StringBuilder(input.length)
    val str = input.to(ListBuffer)

    while str.nonEmpty do
      val c = str.remove(0)

      if c == '<' then
        sb.append(c)
        while str.head != '>' do sb.append(str.remove(0))
        sb.append(str.remove(0))
      else if c == ' ' then sb.append(c)
      else
        val word = StringBuilder()
        word.append(c)
        while str.nonEmpty && str.head != ' ' && str.head != '<' do
          word.append(str.remove(0))
        sb.append(word.reverse)

    sb.toString
