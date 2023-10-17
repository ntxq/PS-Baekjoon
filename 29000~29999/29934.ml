open! StdLabels
open! MoreLabels

let () =
  let contacts =
    let rec loop x acc = if x = 0 then acc else input_line stdin :: acc |> loop (x - 1) in
    loop (input_line stdin |> int_of_string) []
  in
  let rec loop x cnt =
    if x = 0
    then cnt
    else
      (if input_line stdin |> List.mem ~set:contacts then cnt + 1 else cnt) |> loop (x - 1)
  in
  loop (input_line stdin |> int_of_string) 0
  |> Printf.sprintf "%d\n"
  |> output_string stdout
;;
