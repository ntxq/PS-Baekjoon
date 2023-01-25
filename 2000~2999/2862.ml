open! StdLabels
open! MoreLabels

let build_fibonacci len =
  let numbers = Array.make len 0L in
  numbers.(0) <- 1L;
  numbers.(1) <- 1L;

  for i = 2 to len - 1 do
    numbers.(i) <- Int64.add numbers.(i - 1) numbers.(i - 2)
  done;

  numbers

let fibonacci = build_fibonacci 80

let rec max_fibonacci idx x =
  if idx = 80 then -1L
  else if x < fibonacci.(idx) then fibonacci.(idx - 1)
  else max_fibonacci (idx + 1) x

let rec solve x =
  let cur_max = max_fibonacci 0 x in
  if cur_max = x then x else solve (Int64.sub x cur_max)

let () =
  let x = read_line () |> Int64.of_string in
  print_endline (Int64.to_string (solve x))
