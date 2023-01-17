import io.StdIn.*
import annotation.tailrec
import util.chaining.scalaUtilChainingOps

object Main:
  def main(args: Array[String]): Unit =
    for
      _ <- 0 until readInt()
      cube = Cube()
      _ = readInt()
      moves = readLine().split(' ')
    do
      moves foreach { 
        case "F+" => cube.rotateFront()
        case "F-" => cube.rotateFrontCounter()
        case "R+" => cube.rotateRight()
        case "R-" => cube.rotateRightCounter()
        case "L+" => cube.turnLeft()
        case "L-" => cube.turnLeftCounter()
        case "U+" => cube.turnUp()
        case "U-" => cube.turnUpCounter()
        case "B+" => cube.turnBack()
        case "B-" => cube.turnBackCounter()
        case "D+" => cube.turnDown()
        case "D-" => cube.turnDownCounter()
      }
      println(cube)

class Cube:
  var faces = Array.ofDim[Char](54)
  val colors = Array('w', 'g', 'r', 'b', 'y', 'o')

  for
    i <- 0 until 6
    j <- 0 until 9
  do faces(i * 9 + j) = colors(i)

  override def toString: String =
    faces.grouped(3).take(3).map(_.mkString).mkString("\n")

  def rotateFront(): Unit =
    val tmp = Array.ofDim[Char](54)
    (0 until 54) foreach (i => tmp(i) = faces(i))

    tmp(6) = faces(17)
    tmp(7) = faces(14)
    tmp(8) = faces(11)
    tmp(11) = faces(36)
    tmp(14) = faces(37)
    tmp(17) = faces(38)
    tmp(18) = faces(24)
    tmp(19) = faces(21)
    tmp(20) = faces(18)
    tmp(21) = faces(25)
    tmp(22) = faces(22)
    tmp(23) = faces(19)
    tmp(24) = faces(26)
    tmp(25) = faces(23)
    tmp(26) = faces(20)
    tmp(27) = faces(6)
    tmp(30) = faces(7)
    tmp(33) = faces(8)
    tmp(36) = faces(33)
    tmp(37) = faces(30)
    tmp(38) = faces(27)

    faces = tmp

  def rotateFrontCounter(): Unit =
    (0 until 3) foreach (_ => rotateFront())

  def rotateRight(): Unit =
    val tmp = Array.ofDim[Char](54)
    (0 until 54) foreach (i => tmp(i) = faces(i))

    tmp(2) = faces(20);
    tmp(5) = faces(23);
    tmp(8) = faces(26);
    tmp(20) = faces(38);
    tmp(23) = faces(41);
    tmp(26) = faces(44);
    tmp(38) = faces(47);
    tmp(41) = faces(50);
    tmp(44) = faces(53);
    tmp(47) = faces(2);
    tmp(50) = faces(5);
    tmp(53) = faces(8);
    tmp(27) = faces(33);
    tmp(28) = faces(30);
    tmp(29) = faces(27);
    tmp(30) = faces(34);
    tmp(31) = faces(31);
    tmp(32) = faces(28);
    tmp(33) = faces(35);
    tmp(34) = faces(32);
    tmp(35) = faces(29);

    faces = tmp

  def rotateRightCounter(): Unit =
    (0 until 3) foreach (_ => rotateRight())

  def turnLeft(): Unit =
    val tmp = Array.ofDim[Char](54)
    (0 until 54) foreach (i => tmp(i) = faces(i))

    tmp(0) = faces(45);
    tmp(3) = faces(48);
    tmp(6) = faces(51);
    tmp(18) = faces(0);
    tmp(21) = faces(3);
    tmp(24) = faces(6);
    tmp(36) = faces(18);
    tmp(39) = faces(21);
    tmp(42) = faces(24);
    tmp(45) = faces(36);
    tmp(48) = faces(39);
    tmp(51) = faces(42);
    tmp(9) = faces(15);
    tmp(10) = faces(12);
    tmp(11) = faces(9);
    tmp(12) = faces(16);
    tmp(13) = faces(13);
    tmp(14) = faces(10);
    tmp(15) = faces(17);
    tmp(16) = faces(14);
    tmp(17) = faces(11);

    faces = tmp

  def turnLeftCounter(): Unit =
    (0 until 3) foreach (_ => turnLeft())

  def turnUp(): Unit =
    val tmp = Array.ofDim[Char](54)
    (0 until 54) foreach (i => tmp(i) = faces(i))

    tmp(9) = faces(18)
    tmp(10) = faces(19)
    tmp(11) = faces(20)
    tmp(18) = faces(27)
    tmp(19) = faces(28)
    tmp(20) = faces(29)
    tmp(27) = faces(53)
    tmp(28) = faces(52)
    tmp(29) = faces(51)
    tmp(51) = faces(11)
    tmp(52) = faces(10)
    tmp(53) = faces(9)
    tmp(0) = faces(6)
    tmp(1) = faces(3)
    tmp(2) = faces(0)
    tmp(3) = faces(7)
    tmp(4) = faces(4)
    tmp(5) = faces(1)
    tmp(6) = faces(8)
    tmp(7) = faces(5)
    tmp(8) = faces(2)

    faces = tmp

  def turnUpCounter(): Unit =
    (0 until 3) foreach (_ => turnUp())

  def turnBack(): Unit =
    val tmp = Array.ofDim[Char](54)
    (0 until 54) foreach (i => tmp(i) = faces(i))

    tmp(0) = faces(29)
    tmp(1) = faces(32)
    tmp(2) = faces(35)
    tmp(9) = faces(2)
    tmp(12) = faces(1)
    tmp(15) = faces(0)
    tmp(29) = faces(44)
    tmp(32) = faces(43)
    tmp(35) = faces(42)
    tmp(42) = faces(9)
    tmp(43) = faces(12)
    tmp(44) = faces(15)
    tmp(45) = faces(51)
    tmp(46) = faces(48)
    tmp(47) = faces(45)
    tmp(48) = faces(52)
    tmp(49) = faces(49)
    tmp(50) = faces(46)
    tmp(51) = faces(53)
    tmp(52) = faces(50)
    tmp(53) = faces(47)

    faces = tmp

  def turnBackCounter(): Unit =
    (0 until 3) foreach (_ => turnBack())

  def turnDown(): Unit =
    val tmp = Array.ofDim[Char](54)
    (0 until 54) foreach (i => tmp(i) = faces(i))

    tmp(15) = faces(47)
    tmp(16) = faces(46)
    tmp(17) = faces(45)
    tmp(24) = faces(15)
    tmp(25) = faces(16)
    tmp(26) = faces(17)
    tmp(33) = faces(24)
    tmp(34) = faces(25)
    tmp(35) = faces(26)
    tmp(45) = faces(35)
    tmp(46) = faces(34)
    tmp(47) = faces(33)
    tmp(36) = faces(42)
    tmp(37) = faces(39)
    tmp(38) = faces(36)
    tmp(39) = faces(43)
    tmp(40) = faces(40)
    tmp(41) = faces(37)
    tmp(42) = faces(44)
    tmp(43) = faces(41)
    tmp(44) = faces(38)

    faces = tmp

  def turnDownCounter(): Unit =
    (0 until 3) foreach (_ => turnDown())
