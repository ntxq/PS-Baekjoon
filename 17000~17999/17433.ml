open! StdLabels
open! MoreLabels

let rec gcd x y = if y = 0 then x else gcd y (x mod y)

let () =
  for _ = 1 to input_line stdin |> int_of_string do
    let _ = input_line stdin in
    (match
       input_line stdin
       |> String.split_on_char ~sep:' '
       |> List.map ~f:int_of_string
       |> List.sort_uniq ~cmp:Int.compare
     with
     | [] | [ _ ] -> "INFINITY\n"
     | x :: xs ->
       (match List.fold_left_map xs ~init:x ~f:(fun x y -> y, y - x) |> snd with
        | [] -> assert false
        | [ x ] -> x
        | x :: xs -> List.fold_left xs ~init:x ~f:gcd)
       |> Printf.sprintf "%d\n")
    |> output_string stdout
  done
;;
