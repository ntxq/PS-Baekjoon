(* open! Core *)
open! StdLabels

let find_candidate input orig_start mod_start orig_len =
  let rec loop orig modded is_mismatched acc =
    match orig, modded with
    | x :: xs, y :: ys ->
      (match Char.equal x y, is_mismatched with
       | true, _ -> loop xs ys is_mismatched (x :: acc)
       | false, false -> loop orig ys true acc
       | false, true -> [])
    | [], _ | _, [] -> List.rev acc
  in
  let orig =
    String.sub input ~pos:orig_start ~len:orig_len |> String.to_seq |> List.of_seq
  in
  let modded =
    String.sub input ~pos:mod_start ~len:(orig_len + 1) |> String.to_seq |> List.of_seq
  in
  loop orig modded false [] |> List.to_seq |> String.of_seq
;;

let () =
  let len = input_line stdin |> int_of_string in
  let orig_len = len / 2 in
  let input = input_line stdin in
  let output =
    if len mod 2 = 0
    then "NOT POSSIBLE"
    else (
      let candidate_start = find_candidate input 0 orig_len orig_len in
      let candidate_end = find_candidate input (orig_len + 1) 0 orig_len in
      match
        String.(
          ( equal candidate_start ""
          , equal candidate_end ""
          , equal candidate_start candidate_end ))
      with
      | true, true, _ -> "NOT POSSIBLE"
      | true, _, _ -> candidate_end
      | _, true, _ -> candidate_start
      | _, _, true -> candidate_start
      | _, _, false -> "NOT UNIQUE")
  in
  output_string stdout (output ^ "\n")
;;
