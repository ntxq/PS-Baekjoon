open! StdLabels
open! MoreLabels

let calc_score s a t m = s *. (1. +. (1. /. a)) *. (1. +. (m /. t)) /. 4.

let is_the_god yh people size =
  let rec loop gt = function
    | [] -> gt
    | p :: ps -> if p > yh then loop (gt + 1) ps else loop gt ps
  in
  let gt = loop 0 people in
  let total = size + 1 in
  float_of_int (gt + 1) /. float_of_int total <= 0.15
;;

let () =
  let n = input_line stdin |> int_of_string in
  let scores =
    List.init ~len:n ~f:(fun _ ->
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:float_of_string)
  in
  let score =
    List.fold_left scores ~init:0. ~f:(fun acc params ->
      match params with
      | [ s; a; t; m ] -> acc +. calc_score s a t m
      | _ -> assert false)
  in
  let p = input_line stdin |> int_of_string in
  let people = List.init ~len:p ~f:(fun _ -> input_line stdin |> float_of_string) in
  let name = if is_the_god score people p then "Younghoon \"The God\"" else "Younghoon" in
  String.concat
    ~sep:" "
    [ "The total score of"; name; "is"; Format.sprintf "%.2f." score ]
  |> output_string stdout;
  output_char stdout '\n'
;;
