(* open! Core *)
open! StdLabels

let () =
  let t = input_line stdin |> int_of_string in
  for _ = 1 to t do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ n; m; x ] ->
      (if n mod m = x mod m then "YES\n" else "NO\n") |> output_string stdout
    | _ -> assert false
  done
;;
