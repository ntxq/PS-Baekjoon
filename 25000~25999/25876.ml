open! StdLabels
open! MoreLabels

let () =
  let n = input_line stdin |> int_of_string in
  let counts = Array.make (n + 1) 0 in
  for _ = 1 to n do
    let x = input_line stdin |> int_of_string in
    counts.(x) <- counts.(x - 1) + 1
  done;
  Array.fold_left ~f:max ~init:0 counts
  |> ( - ) n
  |> string_of_int
  |> output_string stdout;
  output_char stdout '\n'
;;
