open! StdLabels
open! MoreLabels

let calculate_penalty idx score time = if score = 0 then 0 else time + (idx * 20)

let () =
  let n = input_line stdin |> int_of_string in
  let rec loop idx max_idx max_score max_time =
    if idx = n
    then calculate_penalty max_idx max_score max_time
    else (
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ time; score ] ->
        if score > max_score
        then loop (idx + 1) idx score time
        else loop (idx + 1) max_idx max_score max_time
      | _ -> assert false)
  in
  loop 0 0 0 0 |> string_of_int |> output_string stdout;
  output_char stdout '\n'
;;
