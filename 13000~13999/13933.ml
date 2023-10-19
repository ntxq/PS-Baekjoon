open! StdLabels
open! MoreLabels

let can_be_aligned limit items =
  let rec loop last items =
    match last, items with
    | Some _, [] -> false
    | None, [] -> true
    | None, item :: rest ->
      if item <= limit then loop None rest else loop (Some item) rest
    | Some prev, item :: rest ->
      if item <= limit
      then loop (Some prev) rest
      else if item = prev
      then loop None rest
      else false
  in
  loop None items
;;

let binary_search low high ~f =
  let rec loop low high =
    (* Printf.printf "low: %d, high: %d\n" low high; *)
    if low >= high
    then high
    else (
      let mid = (low + high) / 2 in
      match f mid with
      | true -> loop low mid
      | false -> loop (mid + 1) high)
  in
  loop low high
;;

let () =
  let _ = input_line stdin in
  let row1 =
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  in
  let row2 =
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  in
  binary_search 0 1000000000 ~f:(fun x -> can_be_aligned x row1 && can_be_aligned x row2)
  |> Printf.sprintf "%d\n"
  |> output_string stdout
;;
