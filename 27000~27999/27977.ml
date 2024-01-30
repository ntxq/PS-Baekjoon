(* open! Core *)
open! StdLabels

let is_reachable charge stops battery =
  let rec loop count cur stops =
    if count > charge
    then false
    else (
      match stops with
      | [] -> true
      | x :: [] -> x - cur <= battery
      | x :: y :: rest ->
        if y - cur <= battery
        then loop count cur (y :: rest)
        else if x - cur <= battery
        then loop (count + 1) x (y :: rest)
        else false)
  in
  loop 0 0 stops
;;

let find_kickboard dist charge stops =
  let stops = stops @ [ dist ] in
  let rec loop low high =
    if low = high
    then low
    else (
      let mid = (low + high) / 2 in
      if is_reachable charge stops mid then loop low mid else loop (mid + 1) high)
  in
  loop 0 dist
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ dist; _; charge ] ->
    let result =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> find_kickboard dist charge
    in
    output_string stdout (string_of_int result ^ "\n")
  | _ -> ()
;;
