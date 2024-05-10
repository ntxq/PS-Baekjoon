(* open! Core *)
open! StdLabels
open! MoreLabels

let sieve =
  let is_prime = Array.make 1000000 true in
  is_prime.(0) <- false;
  is_prime.(1) <- false;
  let rec loop idx by =
    if idx >= 1000000
    then ()
    else (
      is_prime.(idx) <- false;
      loop (idx + by) by)
  in
  for i = 2 to 999999 do
    if is_prime.(i) then loop (2 * i) i
  done;
  is_prime
;;

let concat_int x y =
  let rec loop acc x = if x = 0 then acc else loop (acc * 10) (x / 10) in
  loop x y + y
;;

let dp =
  let table = Array.make_matrix ~dimx:1000 ~dimy:1000 0 in
  for i = 1 to 999 do
    for j = 1 to 999 do
      table.(i).(j)
      <- (max table.(i - 1).(j) table.(i).(j - 1)
          + if sieve.(concat_int i j) then 1 else 0)
    done
  done;
  table
;;

let () =
  let n = input_line stdin |> int_of_string in
  string_of_int (dp.(n).(n) - 1) |> output_string stdout;
  output_char stdout '\n'
;;
