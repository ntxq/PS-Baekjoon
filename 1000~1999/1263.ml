open! StdLabels
open! MoreLabels

let schedule_works works =
  let rec loop works time =
    match works with
    | [] -> if time < 0 then -1 else time
    | (t, s) :: works ->
      let time = min time s in
      loop works (time - t)
  in
  loop works max_int
;;

let () =
  let _ = input_line stdin in
  let rec loop acc =
    match input_line stdin with
    | line -> loop (line :: acc)
    | exception End_of_file ->
      List.map acc ~f:(String.split_on_char ~sep:' ')
      |> List.map ~f:(function
        | [ t; s ] -> int_of_string t, int_of_string s
        | _ -> assert false)
      |> List.sort ~cmp:(fun (_, s1) (_, s2) -> Int.compare s2 s1)
  in
  loop [] |> schedule_works |> string_of_int |> output_string stdout;
  output_char stdout '\n'
;;
