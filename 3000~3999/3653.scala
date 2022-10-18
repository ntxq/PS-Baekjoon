import java.io._
import java.nio.file.Files
import java.nio.file.Path
import java.util.StringTokenizer
import scala.annotation.tailrec
import scala.io.Codec

import collection.mutable

class Scanner(reader: LineNumberReader)
    extends Iterator[String]
    with AutoCloseable {
  def this(reader: BufferedReader) = this(new LineNumberReader(reader))
  def this(reader: Reader) = this(new BufferedReader(reader))
  def this(inputStream: InputStream)(implicit codec: Codec) =
    this(new InputStreamReader(inputStream, codec.charSet))
  def this(path: Path)(implicit codec: Codec) =
    this(Files.newBufferedReader(path, codec.charSet))
  def this(file: File)(implicit codec: Codec) = this(file.toPath)(codec)
  def this(str: String) = this(new StringReader(str))

  private[this] val tokenizers = Iterator
    .continually(reader.readLine())
    .takeWhile(_ != null)
    .map(new StringTokenizer(_))
    .filter(_.hasMoreTokens)
  private[this] var current: Option[StringTokenizer] = None

  @inline private[this] def tokenizer(): Option[StringTokenizer] =
    current.find(_.hasMoreTokens) orElse {
      current = if (tokenizers.hasNext) Some(tokenizers.next()) else None
      current
    }

  def nextLine(): String = { current = None; reader.readLine() }
  def lineNumber: Int = reader.getLineNumber
  def nextString(): String = next()
  def nextChar(): Char = next().ensuring(_.length == 1).head
  def nextBoolean(): Boolean = next().toBoolean
  def nextByte(radix: Int = 10): Byte = java.lang.Byte.parseByte(next(), radix)
  def nextShort(radix: Int = 10): Short =
    java.lang.Short.parseShort(next(), radix)
  def nextInt(radix: Int = 10): Int = java.lang.Integer.parseInt(next(), radix)
  def nextLong(radix: Int = 10): Long = java.lang.Long.parseLong(next(), radix)
  def nextBigInt(radix: Int = 10): BigInt = BigInt(next(), radix)
  def nextFloat(): Float = next().toFloat
  def nextDouble(): Double = next().toDouble
  def nextBigDecimal(): BigDecimal = BigDecimal(next())
  override def next() = tokenizer().get.nextToken()
  override def hasNext = tokenizer().nonEmpty
  override def close() = reader.close()
}

object Main:
  private final val sc = Scanner(System.in)
  private final val out = PrintWriter(BufferedOutputStream(System.out))

  def main(args: Array[String]): Unit =
    for _ <- 0 until sc.nextInt()
    do
      val Array(n, m) = sc.nextLine().split(" ").map(_.toInt)
      val segTree = SegmentTree(n, m)

      val dvdPos = mutable.ArraySeq.fill(n + 1)(0)
      for i <- 1 to n do dvdPos(i) = m + i

      val ans = mutable.ArraySeq.fill(m)(0)
      for (dvd, idx) <- sc.nextLine().split(" ").map(_.toInt).zip(0 until m)
      do
        ans(idx) = segTree.query(l = 0, r = dvdPos(dvd) - 1)
        segTree.update(pos = dvdPos(dvd), diff = -1)
        segTree.update(pos = m - idx, diff = 1)
        dvdPos(dvd) = m - idx
      out.println(ans.mkString(" "))
    out.close()

class SegmentTree(n: Int, m: Int):
  private val tree = mutable.ArraySeq.fill((n + m + 1) * 4)(0)
  for i <- m + 1 to n + m
  do update(pos = i, diff = 1)

  final def query(
      v: Int = 1,
      tl: Int = 0,
      tr: Int = n + m,
      l: Int,
      r: Int
  ): Int =
    if l > r then 0
    else if l == tl && r == tr then tree(v)
    else
      val tm = (tl + tr) / 2
      val left = query(v * 2, tl, tm, l, r min tm)
      val right = query(v * 2 + 1, tm + 1, tr, l max (tm + 1), r)
      left + right

  @tailrec
  final def update(
      v: Int = 1,
      tl: Int = 0,
      tr: Int = n + m,
      pos: Int,
      diff: Int
  ): Unit =
    if tl == tr then tree(v) += diff
    else
      val tm = (tl + tr) / 2
      tree(v) += diff
      if pos <= tm then update(v * 2, tl, tm, pos, diff)
      else update(v * 2 + 1, tm + 1, tr, pos, diff)
