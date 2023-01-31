open! StdLabels
open! MoreLabels

let b, c =
  input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  |> function
  | [ _; b; c ] -> (b, c)
  | _ -> assert false

let required = input_line stdin |> String.split_on_char ~sep:' '

let buy_singles () =
  List.fold_left required ~init:0L ~f:(fun acc x ->
      Int64.(add acc (mul (int_of_string x |> of_int) (of_int b))))

let rec buy_combined idx prev_single prev_double acc required =
  if required = [] then acc
  else
    let stock = ref (int_of_string (List.hd required)) in
    let double = min prev_single !stock in
    stock := !stock - double;
    let double_cost = Int64.(mul (of_int double) (of_int c)) in

    let triple = min prev_double !stock in
    stock := !stock - triple;
    let triple_cost = Int64.(mul (of_int triple) (of_int c)) in

    let single = !stock in
    let single_cost = Int64.(mul (of_int single) (of_int b)) in

    buy_combined (idx + 1) single double
      Int64.(add acc single_cost |> add double_cost |> add triple_cost)
      (List.tl required)

let () =
  (if b <= c then buy_singles () else buy_combined 0 0 0 0L required)
  |> Int64.to_string |> output_string stdout
