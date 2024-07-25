open! StdLabels
open! MoreLabels

let bfs a b n is_available =
  let dist = Array.make (n + 1) max_int in
  dist.(0) <- 0;
  for i = 1 to n do
    if is_available.(i)
    then
      dist.(i)
      <- min
           (if i >= a && dist.(i - a) <> max_int then dist.(i - a) + 1 else max_int)
           (if i >= b && dist.(i - b) <> max_int then dist.(i - b) + 1 else max_int)
  done;
  if dist.(n) = max_int then -1 else dist.(n)
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m; a; b ] ->
    let is_available = Array.make (n + 1) true in
    for _ = 1 to m do
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ l; r ] ->
        for i = l to r do
          is_available.(i) <- false
        done
      | _ -> assert false
    done;
    bfs a b n is_available |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
