import io.StdIn.*
import scala.annotation.tailrec

object Main:
  def main(args: Array[String]): Unit =
    val n = readInt()
    for
      i <- 1 to n
      parsedURL = URL(readLine())
    do
      println(s"URL #$i")
      println(parsedURL)

class URL(url: String):
  override def toString(): String =
    val Array(protocol, rest) = url.split("://", 2)

    val default = "<default>"
    (rest.indexOf(":"), rest.indexOf("/")) match
      case (-1, -1) =>
        s"""Protocol = $protocol
Host     = $rest
Port     = $default
Path     = $default
"""
      case (portIdx, -1) =>
        val Array(host, port) = rest.split(":", 2)
        s"""Protocol = $protocol
Host     = $host
Port     = $port
Path     = $default
"""

      case (-1, pathIdx) =>
        val Array(host, path) = rest.split("/", 2)
        s"""Protocol = $protocol
Host     = $host
Port     = $default
Path     = $path
"""

      case (portIdx, pathIdx) if portIdx < pathIdx =>
        val Array(host, rest2) = rest.split(":", 2)
        val Array(port, path) = rest2.split("/", 2)
        s"""Protocol = $protocol
Host     = $host
Port     = $port
Path     = $path
"""

      case _ =>
        val Array(host, path) = rest.split("/", 2)
        s"""Protocol = $protocol
Host     = $host
Port     = $default
Path     = $path
"""
