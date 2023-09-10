open! StdLabels
open! MoreLabels

let () =
  let t = input_line stdin |> int_of_string in
  for _ = 1 to t do
    let _ = input_line stdin in
    let u = input_line stdin |> String.split_on_char ~sep:' ' in
    let v = input_line stdin |> String.split_on_char ~sep:' ' in
    let dist =
      List.fold_left2 u v ~init:0 ~f:(fun acc x y ->
        match String.equal x y with
        | true -> acc
        | false -> acc + 1)
    in
    Printf.sprintf "%d\n" dist |> output_string stdout
  done
;;
