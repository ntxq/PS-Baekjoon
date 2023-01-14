open! StdLabels
open! MoreLabels

let rec fibonacci n =
  let ( * ) x y = Int.mul x y mod 1_000_000 in
  if Int64.equal n 0L then (0, 1)
  else
    let x, y = fibonacci (Int64.shift_right n 1) in
    let c = x * ((2 * y) - x) in
    let d = (x * x) + (y * y) in
    if Int64.logand n 1L |> Int64.equal 0L then (c, d) else (d, c + d)

let () =
  read_line () |> Int64.of_string |> fibonacci |> fst
  |> (fun x -> (x + 1_000_000) mod 1_000_000)
  |> string_of_int |> print_endline
