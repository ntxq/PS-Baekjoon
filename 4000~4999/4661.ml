open! StdLabels
open! MoreLabels

let to_preorder lines =
  let rec loop chars =
    match chars with
    | [ root ] :: rest ->
      let left, right =
        List.map rest ~f:(List.partition ~f:(fun c -> c < root)) |> List.split
      in
      Char.escaped root ^ loop left ^ loop right
    | [] :: rest -> loop rest
    | [] -> ""
    | _ -> assert false
  in
  let chars = List.map lines ~f:(fun line -> String.to_seq line |> List.of_seq) in
  loop chars
;;

let () =
  let rec loop acc =
    match input_line stdin |> String.trim with
    | "*" ->
      to_preorder acc |> output_string stdout;
      output_char stdout '\n';
      loop []
    | "$" ->
      to_preorder acc |> output_string stdout;
      output_char stdout '\n'
    | line -> loop (line :: acc)
  in
  loop []
;;
