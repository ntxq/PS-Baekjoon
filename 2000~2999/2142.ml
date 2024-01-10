(* open! Core *)
open! StdLabels

let is_sorted n m array =
  let rec loop i j =
    if i = n - 1
    then true
    else if j = m - 1
    then loop (i + 1) 0
    else if array.(i).(j) + array.(i + 1).(j + 1) <= array.(i).(j + 1) + array.(i + 1).(j)
    then loop i (j + 1)
    else false
  in
  loop 0 0
;;

let () =
  let rec loop acc =
    match input_line stdin with
    | exception End_of_file -> List.rev acc
    | input ->
      (match String.split_on_char ~sep:' ' input |> List.map ~f:int_of_string with
       | [ n; m ] ->
         let array =
           Array.init n ~f:(fun _ ->
             input_line stdin
             |> String.split_on_char ~sep:' '
             |> List.map ~f:int_of_string
             |> Array.of_list)
         in
         loop (is_sorted n m array :: acc)
       | _ -> assert false)
  in
  let _ = input_line stdin in
  loop [] |> List.iter ~f:(fun b -> output_string stdout (if b then "YES\n" else "NO\n"))
;;
