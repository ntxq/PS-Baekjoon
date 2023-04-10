extension [A, B](x: A) def pipe(f: A => B): B = f(x)

object Main:
  def main(args: Array[String]): Unit =
    (for
      _ <- 0 until io.StdIn.readInt()
      x = io.StdIn.readLong()
    yield Iterator.iterate(x)(_ + 1).find(isPrime).get)
      .mkString("\n")
      .pipe(println)

  def isPrime(x: Long): Boolean =
    if x < 2 then false
    else
      Iterator
        .from(2)
        .takeWhile(i => i.toLong * i.toLong <= x)
        .forall(x % _ != 0)
