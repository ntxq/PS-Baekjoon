open! StdLabels
open! MoreLabels

let calc_as_num a b c = int_of_string a + int_of_string b - int_of_string c
let calc_as_string a b c = a ^ b |> int_of_string |> fun x -> x - int_of_string c

let () =
  let a = input_line stdin in
  let b = input_line stdin in
  let c = input_line stdin in
  Printf.printf "%d\n%d\n" (calc_as_num a b c) (calc_as_string a b c)
;;
