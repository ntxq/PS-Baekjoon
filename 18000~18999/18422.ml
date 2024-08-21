open! StdLabels
open! MoreLabels

let rec dfs x y board visited =
  let dx = [ 0; 0; 1; -1 ] in
  let dy = [ 1; -1; 0; 0 ] in
  visited.(x).(y) <- true;
  List.iter2 dx dy ~f:(fun i j ->
    let nx = x + i in
    let ny = y + j in
    if 0 <= nx
       && nx < Array.length board
       && 0 <= ny
       && ny < Array.length board.(0)
       && (not visited.(nx).(ny))
       && board.(nx).(ny) = '*'
    then dfs nx ny board visited)
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m ] ->
    let board = Array.make_matrix ~dimx:n ~dimy:m '.' in
    for i = 0 to n - 1 do
      input_line stdin |> String.iteri ~f:(fun j c -> board.(i).(j) <- c)
    done;
    let visited = Array.make_matrix ~dimx:n ~dimy:m false in
    let rec loop i j acc =
      if i = n
      then acc
      else if j = m
      then loop (i + 1) 0 acc
      else if (not visited.(i).(j)) && board.(i).(j) = '*'
      then (
        dfs i j board visited;
        loop i (j + 1) (acc + 1))
      else loop i (j + 1) acc
    in
    loop 0 0 0 |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> ()
;;
