(* open! Core *)
open! StdLabels
open! MoreLabels

let min_skip l k =
  let rec loop idx checked unchecked l acc =
    match l with
    | [] -> acc
    | (drop, board) :: tl ->
      let droppable = min drop checked in
      let checked' = checked - droppable in
      let unchecked' = unchecked - (drop - droppable) + board in
      let acc' = acc + (drop - droppable) in
      if idx mod k = 0
      then loop (idx + 1) (checked' + unchecked') 0 tl acc'
      else loop (idx + 1) checked' unchecked' tl acc'
  in
  loop 0 0 0 l 0
;;

let max_skip l k =
  let rec loop idx checked unchecked l acc =
    match l with
    | [] -> acc
    | (drop, board) :: tl ->
      let droppable = min drop unchecked in
      let unchecked' = unchecked - droppable + board in
      let checked' = checked - (drop - droppable) in
      let acc' = acc + droppable in
      if idx mod k = 0
      then loop (idx + 1) (checked' + unchecked') 0 tl acc'
      else loop (idx + 1) checked' unchecked' tl acc'
  in
  loop 0 0 0 l 0
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; k ] ->
    let rec loop i acc =
      if i = n
      then List.rev acc
      else
        input_line stdin
        |> String.split_on_char ~sep:' '
        |> List.map ~f:int_of_string
        |> function
        | [ a; b ] -> loop (i + 1) ((a, b) :: acc)
        | _ -> assert false
    in
    let l = loop 0 [] in
    let min_cost = min_skip l k in
    let max_cost = max_skip l k in
    output_string stdout (string_of_int min_cost ^ " " ^ string_of_int max_cost ^ "\n")
  | _ -> assert false
;;
