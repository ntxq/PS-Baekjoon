open! StdLabels
open! MoreLabels

let rec dfs u adj candies visited =
  visited.(u) <- true;
  List.fold_left
    adj.(u)
    ~init:(1, candies.(u))
    ~f:(fun (size, sum) v ->
      if not visited.(v)
      then (
        let s, c = dfs v adj candies visited in
        size + s, sum + c)
      else size, sum)
;;

let find_comps adj candies =
  let visited = Array.make (Array.length adj) false in
  let rec loop idx acc =
    if idx = Array.length adj
    then acc
    else if visited.(idx)
    then loop (idx + 1) acc
    else loop (idx + 1) (dfs idx adj candies visited :: acc)
  in
  loop 0 []
;;

let find_max_candy adj candies k =
  let comps = find_comps adj candies in
  let knapsack = Array.make k 0 in
  let rec loop comps =
    match comps with
    | [] -> Array.fold_left knapsack ~init:0 ~f:max
    | (size, sum) :: rest ->
      for i = k - 1 downto size do
        knapsack.(i) <- max knapsack.(i) (knapsack.(i - size) + sum)
      done;
      loop rest
  in
  loop comps
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m; k ] ->
    let candies =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> Array.of_list
    in
    let adj = Array.make n [] in
    for _ = 1 to m do
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ u; v ] ->
        adj.(u - 1) <- (v - 1) :: adj.(u - 1);
        adj.(v - 1) <- (u - 1) :: adj.(v - 1)
      | _ -> assert false
    done;
    find_max_candy adj candies k |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
