import io.StdIn.*
import scala.collection.mutable
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    val Array(size, number) = readLine().split(" ")
    LCDNumber.printString(number, size.toInt).foreach(println)

enum LCDNumber:
  case Zero
  case One
  case Two
  case Three
  case Four
  case Five
  case Six
  case Seven
  case Eight
  case Nine

  def topString(size: Int): String =
    this match
      case Zero | Two | Three | Five | Six | Seven | Eight | Nine =>
        " " + "-" * (size) + " "
      case _ =>
        " " * (size + 2)

  def upperString(size: Int): String =
    this match
      case One | Two | Three | Seven =>
        " " * (size + 1) + "|"
      case Zero | Four | Eight | Nine =>
        "|" + " " * (size) + "|"
      case Five | Six =>
        "|" + " " * (size + 1)

  def middleString(size: Int): String =
    this match
      case Zero | One | Seven =>
        " " * (size + 2)
      case _ =>
        " " + "-" * (size) + " "

  def lowerString(size: Int): String =
    this match
      case One | Three | Four | Five | Seven | Nine =>
        " " * (size + 1) + "|"
      case Zero | Six | Eight =>
        "|" + " " * (size) + "|"
      case Two =>
        "|" + " " * (size + 1)

  def bottomString(size: Int): String =
    this match
      case Zero | Two | Three | Five | Six | Eight | Nine =>
        " " + "-" * (size) + " "
      case _ =>
        " " * (size + 2)

  def toLCDString(size: Int): Vector[String] =
    Vector(topString(size))
      ++ Vector.fill(size)(upperString(size))
      ++ Vector(middleString(size))
      ++ Vector.fill(size)(lowerString(size))
      ++ Vector(bottomString(size))

object LCDNumber:
  def printString(number: String, size: Int): Vector[String] =
    number.foldLeft(Vector.empty[String])((acc, char) =>
      val lcdNumber = char.asDigit match
        case 0 => LCDNumber.Zero
        case 1 => LCDNumber.One
        case 2 => LCDNumber.Two
        case 3 => LCDNumber.Three
        case 4 => LCDNumber.Four
        case 5 => LCDNumber.Five
        case 6 => LCDNumber.Six
        case 7 => LCDNumber.Seven
        case 8 => LCDNumber.Eight
        case 9 => LCDNumber.Nine
      val lcdString = lcdNumber.toLCDString(size)
      if acc.isEmpty then lcdString
      else acc.zip(lcdString).map((a, b) => a + " " + b)
    )
