open! StdLabels
open! MoreLabels

let () =
  let dist = read_int () in
  let t = if dist mod 5 = 0 then dist / 5 else (dist / 5) + 1 in
  print_int t
