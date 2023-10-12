open! StdLabels
open! MoreLabels

let count_tasks tasks quiets =
  let rec loop tasks quiets acc =
    match tasks, quiets with
    | [], _ | _, [] -> acc
    | task :: tasks, quiet :: quiets ->
      if task <= quiet
      then loop tasks quiets (acc + 1)
      else loop tasks (quiet :: quiets) acc
  in
  loop
    (List.fast_sort ~cmp:(fun a b -> compare b a) tasks)
    (List.fast_sort ~cmp:(fun a b -> compare b a) quiets)
    0
;;

let () =
  let _ = input_line stdin in
  let tasks =
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  in
  let quiets =
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  in
  count_tasks tasks quiets |> Printf.sprintf "%d\n" |> output_string stdout
;;
