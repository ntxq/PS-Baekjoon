import java.text.SimpleDateFormat
import java.util.Calendar

@main def Main(): Unit =
  val dateFormat = SimpleDateFormat("yyyy-MM-dd")
  val cal = Calendar.getInstance()
  println(dateFormat.format(cal.getTime()))
