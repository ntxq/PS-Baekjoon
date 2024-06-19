open! StdLabels
open! MoreLabels
module IntSet = Set.Make (Int)

let get_subtree_size =
  let memo = Array.make 12000 (-1) in
  let rec get_subtree_size u adj =
    if memo.(u) <> -1
    then memo.(u)
    else
      List.fold_left adj.(u) ~init:0 ~f:(fun acc (v, w) ->
        get_subtree_size v adj + w + acc)
  in
  get_subtree_size
;;

let rec dfs u adj cur_height cur_acc acc =
  match adj.(u) with
  | [] -> max (cur_acc + cur_height) acc
  | _ ->
    let cur_size =
      List.fold_left adj.(u) ~init:0 ~f:(fun acc (v, w) ->
        get_subtree_size v adj + w + acc)
      + cur_height
    in
    List.fold_left adj.(u) ~init:acc ~f:(fun acc (v, w) ->
      dfs v adj (cur_height + w) (cur_acc + cur_size) acc)
;;

let () =
  let n = input_line stdin |> int_of_string in
  let adj = Array.make n [] in
  let in_degree = Array.make n 0 in
  for _ = 2 to n do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ u; v; w ] ->
      adj.(v - 1) <- (u - 1, w) :: adj.(v - 1);
      in_degree.(u - 1) <- in_degree.(u - 1) + 1
    | _ -> assert false
  done;
  let root =
    List.init ~len:n ~f:Fun.id |> List.filter ~f:(fun i -> in_degree.(i) = 0) |> List.hd
  in
  dfs root adj 0 0 0 |> string_of_int |> output_string stdout;
  output_char stdout '\n'
;;
