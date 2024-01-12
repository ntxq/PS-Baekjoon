(* open! Core *)
open! StdLabels

let cut_trees inside stock count required =
  let inside = List.fast_sort inside ~cmp:(fun h1 h2 -> h2 - h1) in
  let rec loop trees stock count =
    if stock >= required
    then count
    else (
      match trees with
      | [] -> max_int
      | h :: hs -> loop hs (stock + h) (count + 1))
  in
  loop inside stock count
;;

let make_fence n trees =
  let trees_x = Array.copy trees in
  let trees_y = Array.copy trees in
  Array.fast_sort trees_x ~cmp:(fun (x1, _, _) (x2, _, _) -> x1 - x2);
  Array.fast_sort trees_y ~cmp:(fun (_, y1, _) (_, y2, _) -> y1 - y2);
  let rec loop xi xj yi yj acc =
    if xi = n
    then acc
    else if xj = n
    then loop (xi + 1) (xi + 1) 0 0 acc
    else if yi = n
    then loop xi (xj + 1) 0 0 acc
    else if yj = n
    then loop xi xj (yi + 1) (yi + 1) acc
    else (
      let cur_trees = [ trees_x.(xi); trees_x.(xj); trees_y.(yi); trees_y.(yj) ] in
      let min_x =
        List.fold_left cur_trees ~init:max_int ~f:(fun acc (x, _, _) -> min acc x)
      in
      let max_x =
        List.fold_left cur_trees ~init:min_int ~f:(fun acc (x, _, _) -> max acc x)
      in
      let min_y =
        List.fold_left cur_trees ~init:max_int ~f:(fun acc (_, y, _) -> min acc y)
      in
      let max_y =
        List.fold_left cur_trees ~init:min_int ~f:(fun acc (_, y, _) -> max acc y)
      in
      let inside, stock, count =
        Array.fold_left trees ~init:([], 0, 0) ~f:(fun (inside, stock, count) (x, y, h) ->
          if min_x <= x && x <= max_x && min_y <= y && y <= max_y
          then h :: inside, stock, count
          else inside, stock + h, count + 1)
      in
      let required = ((max_x - min_x) * 2) + ((max_y - min_y) * 2) in
      let total_count = cut_trees inside stock count required in
      loop xi xj yi (yj + 1) (min acc total_count))
  in
  loop 0 0 0 0 max_int
;;

let () =
  let n = input_line stdin |> int_of_string in
  let trees = Array.make n (0, 0, 0) in
  for i = 0 to n - 1 do
    let tree =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> function
      | [ x; y; h ] -> x, y, h
      | _ -> assert false
    in
    trees.(i) <- tree
  done;
  let count = make_fence n trees in
  output_string stdout (string_of_int count ^ "\n")
;;
