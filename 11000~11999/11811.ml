open! StdLabels
open! MoreLabels

let () =
  let n = input_line stdin |> int_of_string in
  for _ = 1 to n do
    let num =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> List.fold_left ~init:0 ~f:( lor )
    in
    output_string stdout (Printf.sprintf "%d " num)
  done;
  output_char stdout '\n'
;;
