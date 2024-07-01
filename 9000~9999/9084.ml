open! StdLabels
open! MoreLabels

let handle_case () =
  let _ = input_line stdin |> int_of_string in
  let coins =
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  in
  let target = input_line stdin |> int_of_string in
  let knapsack = Array.make (target + 1) 0 in
  knapsack.(0) <- 1;
  List.iter coins ~f:(fun coin ->
    for i = coin to target do
      knapsack.(i) <- knapsack.(i) + knapsack.(i - coin)
    done);
  string_of_int knapsack.(target) |> output_string stdout;
  output_char stdout '\n'
;;

let () =
  let t = input_line stdin |> int_of_string in
  for _ = 1 to t do
    handle_case ()
  done
;;
