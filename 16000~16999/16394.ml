open! StdLabels
open! MoreLabels

let () =
  input_line stdin |> int_of_string |> Int.add (-1946) |> string_of_int
  |> fun s -> output_string stdout (s ^ "\n")
