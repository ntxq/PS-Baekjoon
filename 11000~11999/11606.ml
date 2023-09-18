open! StdLabels
open! MoreLabels

let rec drop_test n safe break =
  if n = 0
  then safe, break
  else (
    match input_line stdin |> String.split_on_char ~sep:' ' with
    | [ l; "SAFE" ] ->
      let l = int_of_string l in
      drop_test (n - 1) (max safe l) break
    | [ h; "BROKEN" ] ->
      let h = int_of_string h in
      drop_test (n - 1) safe (min break h)
    | _ -> assert false)
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; k ] ->
    let l, h = drop_test n 1 k in
    Printf.sprintf "%d %d\n" (l + 1) (h - 1) |> output_string stdout
  | _ -> assert false
;;
