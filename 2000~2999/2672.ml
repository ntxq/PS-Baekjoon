(* open! Core *)
open! StdLabels

let parse_input () =
  let _ = input_line stdin in
  let rec loop acc =
    match
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:float_of_string
      |> List.map ~f:(fun x -> int_of_float (x *. 10.))
    with
    | exception End_of_file -> acc
    | [ x; y; w; h ] -> loop ((x + w, y, h, -1) :: (x, y, h, 1) :: acc)
    | _ -> assert false
  in
  loop [] |> List.sort ~cmp:(fun (x1, _, _, _) (x2, _, _, _) -> x1 - x2)
;;

let sweep_lines points =
  let line = Array.make 20001 0 in
  let rec loop points last_x acc =
    match points with
    | [] -> acc
    | (x, y, h, d) :: rest ->
      let acc =
        (Array.fold_left line ~init:0 ~f:(fun acc b -> if b > 0 then acc + 1 else acc)
         * (x - last_x))
        + acc
      in
      for i = y to y + h - 1 do
        line.(i) <- line.(i) + d
      done;
      loop rest x acc
  in
  loop points 0 0
;;

let () =
  let result = parse_input () |> sweep_lines in
  output_string stdout (string_of_int (result / 100));
  if result mod 100 <> 0
  then (
    output_string stdout ".";
    output_string stdout (string_of_int (result mod 100 / 10));
    output_string stdout (string_of_int (result mod 10)))
;;
