open! StdLabels
open! MoreLabels

let factors n =
  let rec loop i acc =
    if i > n
    then acc
    else if n mod i = 0
    then loop (i + 1) (i :: acc)
    else loop (i + 1) acc
  in
  loop 1 []
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ p; q ] ->
    let ys = factors q |> List.rev in
    factors p
    |> List.rev
    |> List.iter ~f:(fun x ->
      List.iter ys ~f:(fun y -> Printf.sprintf "%d %d\n" x y |> output_string stdout))
  | _ -> assert false
;;
