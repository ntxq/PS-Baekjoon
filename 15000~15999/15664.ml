open! StdLabels
open! MoreLabels

let rec select xs cur m acc =
  match xs, m with
  | _, 0 -> List.rev cur :: acc
  | [], _ -> acc
  | y :: ys, m -> select ys (y :: cur) (m - 1) acc |> select ys cur m
;;

let print_list xs =
  List.map xs ~f:string_of_int |> String.concat ~sep:" " |> output_string stdout;
  output_char stdout '\n'
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ _; m ] ->
    let xs =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> List.fast_sort ~cmp:compare
    in
    select xs [] m [] |> List.sort_uniq ~cmp:compare |> List.iter ~f:print_list
  | _ -> assert false
;;
