(* open! Core *)
open! StdLabels

let base = 1000000007
let rec fact n acc = if n = 0 then acc else fact (n - 1) (n * acc mod base)

let binpow x y =
  let rec aux x y acc =
    if y = 0
    then acc
    else aux (x * x mod base) (y / 2) (if y mod 2 = 0 then acc else acc * x mod base)
  in
  aux x y 1
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ a; b ] ->
    let n = fact a 1 in
    let m = fact b 1 |> fact (a - b) in
    let res = n * binpow m (base - 2) mod base in
    output_string stdout (string_of_int res ^ "\n")
  | _ -> assert false
;;
