(* open! Core *)
open! StdLabels
open! MoreLabels

let base = 998244353L

let dp =
  let dp = Array.make_matrix ~dimx:50300 ~dimy:8 0L in
  dp.(0).(0) <- 1L;
  let rec loop x y =
    if x = 50300
    then ()
    else if y = 8
    then loop (x + 1) 0
    else if y = 0
    then (
      let prod = Int64.mul dp.(x - 1).(y) 6L in
      dp.(x).(y) <- Int64.rem prod base;
      loop x (y + 1))
    else if y = 7
    then (
      let prev = dp.(x - 1).(y - 1) in
      let prod = Int64.mul dp.(x - 1).(y) 7L in
      let sum = Int64.add prev prod in
      dp.(x).(y) <- Int64.rem sum base;
      loop x (y + 1))
    else (
      let prev = dp.(x - 1).(y - 1) in
      let prod = Int64.mul dp.(x - 1).(y) 6L in
      let sum = Int64.add prev prod in
      dp.(x).(y) <- Int64.rem sum base;
      loop x (y + 1))
  in
  loop 1 0;
  dp
;;

let () =
  let s = input_line stdin |> int_of_string in
  Int64.to_string dp.(s).(7) |> output_string stdout;
  output_char stdout '\n'
;;
