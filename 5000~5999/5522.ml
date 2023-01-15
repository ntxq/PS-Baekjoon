open! StdLabels
open! MoreLabels

let () =
  List.init ~len:5 ~f:(fun _ -> read_int ())
  |> List.fold_left ~init:0 ~f:Int.add
  |> string_of_int |> print_endline
