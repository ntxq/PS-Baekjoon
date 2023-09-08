open! StdLabels
open! MoreLabels

let is_safe c =
  let is_non_zero c =
    string_of_int c |> String.to_seq |> List.of_seq |> List.for_all ~f:(fun c -> c <> '0')
  in
  let is_all_unique c =
    let module S = Set.Make (Char) in
    string_of_int c |> String.to_seq |> S.of_seq |> S.cardinal |> Int.equal 6
  in
  let is_divisible c =
    string_of_int c
    |> String.to_seq
    |> List.of_seq
    |> List.map ~f:(fun c -> int_of_char c - int_of_char '0')
    |> List.for_all ~f:(fun i -> c mod i = 0)
  in
  is_non_zero c && is_all_unique c && is_divisible c
;;

let count_pwd l h =
  let rec loop acc i =
    match i > h with
    | true -> acc
    | false -> loop (if is_safe i then acc + 1 else acc) (i + 1)
  in
  loop 0 l
;;

let () =
  let l, h =
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ l; h ] -> l, h
    | _ -> assert false
  in
  count_pwd l h |> string_of_int |> output_string stdout;
  output_char stdout '\n'
;;
