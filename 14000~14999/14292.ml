open! StdLabels
open! MoreLabels

let find_base_length x base =
  let rec loop n prod acc =
    if prod > n
    then false
    else if prod = n
    then true
    else loop (n - prod) (prod * base) (acc + 1)
  in
  loop x 1 1
;;

let find_max_base_length x =
  let rec loop base = if find_base_length x base then base else loop (base + 1) in
  loop 2
;;

let () =
  let t = input_line stdin |> int_of_string in
  let rec loop idx =
    if idx = t
    then ()
    else (
      let x = input_line stdin |> int_of_string in
      let len = find_max_base_length x in
      Printf.printf "Case #%d: %d\n" (idx + 1) len;
      loop (idx + 1))
  in
  loop 0
;;
