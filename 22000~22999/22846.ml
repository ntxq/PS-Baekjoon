open! StdLabels
open! MoreLabels

let () =
  (match input_line stdin |> int_of_string with
   | 2 | 6 -> "Kali\n"
   | _ -> "Ringo\n")
  |> output_string stdout
;;
