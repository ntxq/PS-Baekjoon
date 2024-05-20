(* open! Core *)
open! StdLabels
open! MoreLabels

let rec invest options total_profit total_cost retire_day =
  match options with
  | [] -> retire_day
  | (p, c) :: rest ->
    let open Int64 in
    let day = (c + p - 1) / p |> of_int in
    if day > retire_day
    then retire_day
    else (
      let cost = add total_cost (of_int c) in
      let profit = add total_profit (of_int p) in
      let new_day = div (sub (add cost profit) one) profit in
      invest rest profit cost new_day)
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m ] ->
    let options = Array.make n (0, 0) in
    for i = 1 to n do
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ p; c ] -> options.(i - 1) <- p, c
      | _ -> assert false
    done;
    Array.fast_sort options ~cmp:(fun (p1, c1) (p2, c2) ->
      let day1 = (c1 + p1 - 1) / p1 in
      let day2 = (c2 + p2 - 1) / p2 in
      Int.compare day1 day2);
    invest (Array.to_list options) 0L (Int64.of_int m) Int64.max_int
    |> Int64.to_string
    |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
