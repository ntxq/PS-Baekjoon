(* open! Core *)
open! StdLabels
open! MoreLabels

let make_dp n m pond =
  let column_sum = Array.make_matrix ~dimx:n ~dimy:m 0 in
  for i = 0 to n - 1 do
    for j = 0 to m - 1 do
      column_sum.(i).(j) <- (pond.(i).(j) + if i > 0 then column_sum.(i - 1).(j) else 0)
    done
  done;
  let dp = Array.make_matrix ~dimx:n ~dimy:m 0 in
  for i = 0 to n - 1 do
    for j = 0 to m - 1 do
      dp.(i).(j)
      <- (pond.(i).(j)
          + (if i > 0 then dp.(i - 1).(j) else 0)
          + if i > 0 && j > 0 then dp.(i - 1).(j - 1) else 0)
    done
  done;
  dp
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m; q ] ->
    let pond = Array.make_matrix ~dimx:n ~dimy:m 0 in
    for i = 0 to n - 1 do
      let row =
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      in
      List.iteri row ~f:(fun j x -> pond.(i).(j) <- x)
    done;
    let dp = make_dp n m pond in
    for _ = 0 to q - 1 do
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ w; p ] ->
        dp.(w - 1).(p - 1) |> string_of_int |> output_string stdout;
        output_char stdout '\n'
      | _ -> assert false
    done
  | _ -> assert false
;;
