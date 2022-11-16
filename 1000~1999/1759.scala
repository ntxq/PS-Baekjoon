import io.StdIn.*

object Main:
  def main(args: Array[String]): Unit =
    println(
      Function.tupled(allPasswords)(readInput()).mkString("\n")
    )

  def readInput(): (Vector[Char], Vector[Char], Int) =
    val Array(l, c) = readLine().split(" ").map(_.toInt)
    val chars = readLine().split(" ").map(_.head).toVector
    val groups = chars.groupBy(Set('a', 'e', 'i', 'o', 'u').contains(_))

    (groups(true), groups(false), l)

  def allPasswords(
      vowels: Vector[Char],
      consonants: Vector[Char],
      length: Int
  ): Vector[String] =
    val passwords = for
      vowelCount <- 1 to length - 2
      consonantCount = length - vowelCount
      vowels <- vowels.combinations(vowelCount)
      consonants <- consonants.combinations(consonantCount)
    yield (vowels ++ consonants).sorted.mkString
    passwords.sorted.toVector
