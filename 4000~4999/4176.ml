open! StdLabels
open! MoreLabels

let rec digits_sequence x i =
  let len = string_of_int x |> String.length in
  match len = x with
  | true -> i
  | false -> digits_sequence len (i + 1)
;;

let rec handle_input () =
  match input_line stdin with
  | "END" -> ()
  | "1" ->
    output_string stdout "1\n";
    handle_input ()
  | num ->
    digits_sequence (String.length num) 2 |> string_of_int |> output_string stdout;
    output_char stdout '\n';
    handle_input ()
;;

let () = handle_input ()
