(* open! Core *)
open! StdLabels

let travel target stops moves =
  let dp = Array.make (target + 1) (-1) in
  for i = stops.(0) to min (stops.(0) + moves.(0)) target do
    dp.(i) <- 0
  done;
  let rec loop cur_idx cur_dp =
    if cur_idx = Array.length stops
    then dp.(target)
    else if cur_dp < stops.(cur_idx)
    then -1
    else if stops.(cur_idx) + moves.(cur_idx) <= cur_dp
    then loop (cur_idx + 1) cur_dp
    else (
      let next_dp = stops.(cur_idx) + moves.(cur_idx) in
      for i = cur_dp + 1 to min next_dp target do
        dp.(i) <- dp.(stops.(cur_idx)) + 1
      done;
      loop (cur_idx + 1) next_dp)
  in
  loop 1 (stops.(0) + moves.(0))
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ _; m ] ->
    let stops =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> Array.of_list
    in
    let moves =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> Array.of_list
    in
    let ans = travel m stops moves in
    output_string stdout (string_of_int ans ^ "\n")
  | _ -> assert false
;;
