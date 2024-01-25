(* open! Core *)
open! StdLabels

let max_colors = 20
let graph = Array.make 100001 []
let dp = Bigarray.Array2.create Bigarray.int64 Bigarray.c_layout 100001 max_colors

let rec solve cur prev color =
  let rec loop next i acc =
    if i = max_colors
    then acc
    else if i = color
    then loop next (i + 1) acc
    else loop next (i + 1) (min acc (solve next cur i))
  in
  if Bigarray.Array2.get dp cur color = -1L
  then (
    let subcost =
      List.fold_left graph.(cur) ~init:0L ~f:(fun acc next ->
        if next = prev then acc else Int64.add acc (loop next 1 Int64.max_int))
    in
    Bigarray.Array2.set dp cur color (Int64.add subcost (Int64.of_int color)));
  Bigarray.Array2.get dp cur color
;;

let () =
  let n = input_line stdin |> int_of_string in
  for _ = 1 to n - 1 do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ u; v ] ->
      graph.(u) <- v :: graph.(u);
      graph.(v) <- u :: graph.(v)
    | _ -> assert false
  done;
  Bigarray.Array2.fill dp (-1L);
  let rec loop i acc =
    if i = max_colors then acc else loop (i + 1) (min acc (solve 1 0 i))
  in
  output_string stdout ((loop 1 Int64.max_int |> Int64.to_string) ^ "\n")
;;
