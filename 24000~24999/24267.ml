open! StdLabels
open! MoreLabels

let () =
  let n = read_int () in
  let cnt = n * (n - 1) * (n - 2) / 6 in
  Printf.printf "%d\n3\n" cnt
