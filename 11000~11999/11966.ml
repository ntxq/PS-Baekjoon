open! Core

let rec is_multiple_of_2 n =
  if n = 1 then true else if n mod 2 = 0 then is_multiple_of_2 (n / 2) else false
;;

let () =
  In_channel.input_line_exn In_channel.stdin
  |> Int.of_string
  |> is_multiple_of_2
  |> Bool.to_int
  |> Int.to_string
  |> Out_channel.output_string stdout
;;
