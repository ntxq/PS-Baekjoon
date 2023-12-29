(* open! Core *)
open StdLabels

let time_before h1 min1 h2 min2 = h1 < h2 || (h1 = h2 && min1 <= min2)

let () =
  match
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.concat_map ~f:(String.split_on_char ~sep:':')
    |> List.map ~f:int_of_string
  with
  | [ sh; smin; lh; lmin; fh; fmin ] ->
    let module StrSet = Set.Make (String) in
    let rec loop before after =
      match input_line stdin with
      | exception End_of_file -> StrSet.inter before after |> StrSet.cardinal
      | line ->
        (match String.split_on_char line ~sep:' ' with
         | [ time; name ] ->
           (match String.split_on_char time ~sep:':' |> List.map ~f:int_of_string with
            | [ h; min ] ->
              if time_before h min sh smin
              then loop (StrSet.add name before) after
              else if time_before lh lmin h min && time_before h min fh fmin
              then loop before (StrSet.add name after)
              else loop before after
            | _ -> loop before after)
         | _ -> 0)
    in
    loop StrSet.empty StrSet.empty |> string_of_int |> output_string stdout
  | _ -> ()
;;
