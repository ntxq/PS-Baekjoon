open! StdLabels
open! MoreLabels

let drop_min_max scores to_drop =
  let rec loop scores to_drop acc =
    match to_drop, scores with
    | 0, x :: xs -> loop xs 0 (x :: acc)
    | _, [] -> acc
    | _, _ :: xs -> loop xs (to_drop - 1) acc
  in
  let scores = loop scores to_drop [] in
  loop scores to_drop []
;;

let () =
  let n = input_line stdin |> int_of_string in
  let scores =
    List.init ~len:n ~f:(fun _ -> input_line stdin |> int_of_string)
    |> List.fast_sort ~cmp:Int.compare
  in
  let to_drop = float_of_int n *. 0.15 |> Float.round |> int_of_float in
  drop_min_max scores to_drop
  |> List.fold_left ~init:0 ~f:( + )
  |> float_of_int
  |> (fun sum -> sum /. float_of_int (n - (2 * to_drop)))
  |> Float.round
  |> int_of_float
  |> string_of_int
  |> output_string stdout;
  output_char stdout '\n'
;;
