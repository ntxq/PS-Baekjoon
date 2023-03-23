open! StdLabels
open! MoreLabels

let () =
  Scanf.scanf "%d %d %d" (fun x y z ->
      if x = 60 && y = 60 && z = 60 then "Equilateral"
      else if x + y + z != 180 then "Error"
      else if x = y || y = z || z = x then "Isosceles"
      else "Scalene")
  |> print_endline
