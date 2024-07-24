# 0 "bin/main.ml"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "bin/main.ml"
open! StdLabels
open! MoreLabels

let is_k_sejun n k =
  let rec loop n d =
    if d * d > n
    then n <= k
    else if n mod d = 0
    then if d > k then false else loop (n / d) d
    else loop n (d + 1)
  in
  loop n 2
;;

let count_sejun n k =
  List.init ~len:n ~f:(fun i -> i + 1)
  |> List.filter ~f:(fun x -> is_k_sejun x k)
  |> List.length
;;

let () =
  let n = input_line stdin |> int_of_string in
  let k = input_line stdin |> int_of_string in
  count_sejun n k |> string_of_int |> output_string stdout;
  output_char stdout '\n'
;;
