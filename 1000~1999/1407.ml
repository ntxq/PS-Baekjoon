open! StdLabels
open! MoreLabels

let rec sum_of_2s x =
  match x, x mod 2 with
  | 0, _ -> 0
  | 1, _ -> 1
  | _, 0 -> (x / 2) + (2 * sum_of_2s (x / 2))
  | _, _ -> (x / 2) + (2 * sum_of_2s (x / 2)) + 1
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ a; b ] ->
    sum_of_2s b - sum_of_2s (a - 1) |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> ()
;;
