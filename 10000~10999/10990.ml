open! StdLabels
open! MoreLabels

let make_stars len =
  let rec make_row acc x =
    if x > len
    then acc
    else if x = 1
    then (
      let row = String.make (len - 1) ' ' ^ "*\n" in
      make_row (row :: acc) (x + 1))
    else (
      let prefix = String.make (len - x) ' ' in
      let middle = String.make ((2 * x) - 3) ' ' in
      let row = prefix ^ "*" ^ middle ^ "*\n" in
      make_row (row :: acc) (x + 1))
  in
  make_row [] 1 |> List.rev |> String.concat ~sep:""
;;

let () = input_line stdin |> int_of_string |> make_stars |> output_string stdout
