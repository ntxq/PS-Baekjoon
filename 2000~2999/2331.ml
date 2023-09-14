open! StdLabels
open! MoreLabels

let rec power base exp = if exp = 0 then 1 else base * power base (exp - 1)

let count_duplicate_seq a p =
  let memo = Hashtbl.create 100 in
  Hashtbl.add memo ~key:a ~data:0;
  let rec loop i dist =
    let next =
      string_of_int i
      |> String.to_seq
      |> Seq.fold_left (fun acc x -> acc + power (Char.code x - Char.code '0') p) 0
    in
    match Hashtbl.mem memo next with
    | true -> Hashtbl.find memo next
    | false ->
      Hashtbl.add memo ~key:next ~data:dist;
      loop next (dist + 1)
  in
  loop a 1
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ a; p ] -> count_duplicate_seq a p |> Printf.sprintf "%d\n" |> print_string
  | _ -> assert false
;;
