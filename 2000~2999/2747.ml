open! StdLabels
open! MoreLabels

let fib n =
  let rec loop prev cur idx =
    if idx = 0 then prev else loop cur (prev + cur) (idx - 1)
  in
  loop 0 1 n

let () = Scanf.scanf "%d" (fun n -> fib n |> Printf.printf "%d\n")
