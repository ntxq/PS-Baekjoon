(* open! Core *)
open! StdLabels

let () =
  let n = input_line stdin |> int_of_string in
  for _ = 1 to n do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ u; v ] ->
      let dist = v - u |> float_of_int |> sqrt |> int_of_float in
      if u = v
      then Printf.printf "0\n"
      else if dist * dist = v - u
      then Printf.printf "%d\n" ((dist * 2) - 1)
      else if (dist * dist) + dist < v - u
      then Printf.printf "%d\n" ((dist * 2) + 1)
      else Printf.printf "%d\n" (dist * 2)
    | _ -> assert false
  done
;;
