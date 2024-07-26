open! StdLabels
open! MoreLabels

let rec dfs sx sy n vertical horizontal visited order =
  visited.(sx).(sy) <- true;
  let order =
    if sx > 0 && (not visited.(sx - 1).(sy)) && vertical.(sx - 1).(sy) = '>'
    then dfs (sx - 1) sy n vertical horizontal visited order
    else order
  in
  let order =
    if sx < n - 1 && (not visited.(sx + 1).(sy)) && vertical.(sx).(sy) = '<'
    then dfs (sx + 1) sy n vertical horizontal visited order
    else order
  in
  let order =
    if sy > 0 && (not visited.(sx).(sy - 1)) && horizontal.(sx).(sy - 1) = '>'
    then dfs sx (sy - 1) n vertical horizontal visited order
    else order
  in
  let order =
    if sy < n - 1 && (not visited.(sx).(sy + 1)) && horizontal.(sx).(sy) = '<'
    then dfs sx (sy + 1) n vertical horizontal visited order
    else order
  in
  (sx, sy) :: order
;;

let topological_order n vertical horizontal =
  let visited = Array.make_matrix ~dimx:n ~dimy:n false in
  let rec loop x y order =
    if x = n
    then order
    else if y = n
    then loop (x + 1) 0 order
    else if visited.(x).(y)
    then loop x (y + 1) order
    else loop x (y + 1) (dfs x y n vertical horizontal visited order)
  in
  loop 0 0 []
;;

let () =
  let n = input_line stdin |> int_of_string in
  let horizontal =
    Array.init n ~f:(fun _ ->
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:(fun s -> s.[0])
      |> Array.of_list)
  in
  let vertical =
    Array.init (n - 1) ~f:(fun _ ->
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:(fun s -> s.[0])
      |> Array.of_list)
  in
  let board = Array.make_matrix ~dimx:n ~dimy:n 0 in
  let rec loop idx order =
    match order with
    | [] -> ()
    | (x, y) :: rest ->
      board.(x).(y) <- idx;
      loop (idx + 1) rest
  in
  loop 1 (topological_order n vertical horizontal);
  Array.iter board ~f:(fun row ->
    Array.iter row ~f:(fun x ->
      string_of_int x |> output_string stdout;
      output_char stdout ' ');
    output_char stdout '\n')
;;
