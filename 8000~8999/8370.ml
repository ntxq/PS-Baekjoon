open! StdLabels
open! MoreLabels

let () =
  input_line stdin
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string
  |> (function [ n1; k1; n2; k2 ] -> (n1 * k1) + (n2 * k2) | _ -> 0)
  |> Printf.printf "%d\n"
