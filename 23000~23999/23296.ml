(* open! Core *)
open! StdLabels

let get_candidates dest n =
  let in_degree = Array.make n false in
  Array.iter dest ~f:(fun i -> in_degree.(i) <- true);
  let rec loop idx acc =
    if idx = n
    then acc
    else if in_degree.(idx)
    then loop (idx + 1) acc
    else loop (idx + 1) (idx :: acc)
  in
  loop 0 []
;;

let get_not_visited visited n =
  let rec loop idx acc =
    if idx = n
    then acc
    else if visited.(idx)
    then loop (idx + 1) acc
    else loop (idx + 1) (idx :: acc)
  in
  loop 0 []
;;

let () =
  let n = input_line stdin |> int_of_string in
  let dest =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> List.map ~f:pred
    |> Array.of_list
  in
  let visited = Array.make n false in
  let rec visit idx acc =
    if visited.(idx)
    then acc
    else (
      visited.(idx) <- true;
      visit dest.(idx) (dest.(idx) :: acc))
  in
  let rec loop to_visit acc =
    match to_visit with
    | [] -> List.rev acc |> List.map ~f:succ
    | idx :: rest ->
      if visited.(idx) then loop rest acc else loop rest (visit idx (idx :: acc))
  in
  let res_1 = loop (0 :: get_candidates dest n) [] |> List.tl in
  let res_2 = loop (get_not_visited visited n) [] in
  let res = res_1 @ res_2 |> List.map ~f:string_of_int in
  output_string stdout (List.length res |> string_of_int);
  output_char stdout '\n';
  output_string stdout (String.concat res ~sep:" ");
  output_char stdout '\n'
;;
