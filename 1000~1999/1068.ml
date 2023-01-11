open StdLabels
(* open MoreLabels *)

let rec countLeaves adj = function
  | [] -> 1
  | xs ->
      List.fold_left xs ~init:0 ~f:(fun acc x -> acc + countLeaves adj adj.(x))

let () =
  let root = ref 0 in
  let adj = Array.make (read_int ()) [] in
  read_line ()
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string
  |> List.iteri ~f:(fun i p ->
         if p = -1 then root := i else adj.(p) <- i :: adj.(p));
  let to_delete = read_int () in
  let adj_deleted =
    Array.map adj ~f:(List.filter ~f:(fun x -> x <> to_delete))
  in
  if !root <> to_delete then
    countLeaves adj_deleted [ !root ] |> string_of_int |> print_endline
  else "0" |> print_endline
