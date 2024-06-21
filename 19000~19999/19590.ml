open! StdLabels
open! MoreLabels

let () =
  let n = input_line stdin |> int_of_string in
  let rec loop i acc =
    if i = n
    then List.fast_sort acc ~cmp:Int64.compare |> Array.of_list
    else (
      let num = input_line stdin |> Int64.of_string in
      loop (i + 1) (num :: acc))
  in
  let beads = loop 0 [] in
  let sum = Array.fold_left beads ~init:0L ~f:Int64.add in
  let max_bead = beads.(n - 1) in
  (if Int64.sub sum max_bead < max_bead
   then (
     let prod = Int64.mul max_bead 2L in
     Int64.sub prod sum)
   else Int64.rem sum 2L)
  |> Int64.to_string
  |> output_string stdout;
  output_char stdout '\n'
;;
