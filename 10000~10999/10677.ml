(* open! Core *)
open! StdLabels
open! MoreLabels

let num_in_base base num =
  let rec loop num = if num = 0 then 0 else (loop (num / 10) * base) + (num mod 10) in
  loop num
;;

let find_bases a b =
  let base_map = Hashtbl.create 15000 in
  let rec loop_fill base =
    if base > 15000
    then ()
    else (
      let num = num_in_base base a in
      Hashtbl.add base_map ~key:num ~data:base;
      loop_fill (base + 1))
  in
  loop_fill 10;
  let rec loop_find base =
    let num = num_in_base base b in
    match Hashtbl.find_opt base_map num with
    | Some base_a -> base_a, base
    | None -> loop_find (base + 1)
  in
  loop_find 10
;;

let () =
  let k = input_line stdin |> int_of_string in
  for _ = 1 to k do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ a; b ] ->
      let x, y = find_bases a b in
      output_string stdout (string_of_int x ^ " " ^ string_of_int y ^ "\n")
    | _ -> assert false
  done
;;
