(* open! Core *)
open! StdLabels

let rec xgcd a b =
  if b = 0
  then a, 1, 0
  else (
    let d, x, y = xgcd b (a mod b) in
    d, y, x - (y * (a / b)))
;;

let mmi a m =
  let _, x, _ = xgcd a m in
  ((x mod m) + m) mod m
;;

let mod_base = 1_000_000_007

let factorial n =
  let rec loop acc = function
    | 0 -> acc
    | n -> loop (acc * n mod mod_base) (n - 1)
  in
  loop 1 n
;;

let count_pizzas pizzas =
  let suffix_sum = Array.copy pizzas in
  for i = Array.length pizzas - 2 downto 0 do
    suffix_sum.(i) <- (suffix_sum.(i) + suffix_sum.(i + 1)) mod mod_base
  done;
  let total_count =
    Array.fold_left
      pizzas
      ~init:(factorial suffix_sum.(0))
      ~f:(fun acc x -> acc * mmi (factorial x) mod_base mod mod_base)
  in
  Array.mapi pizzas ~f:(fun idx x ->
    total_count * x mod mod_base * mmi suffix_sum.(idx) mod_base mod mod_base)
  |> Array.fold_left ~init:0 ~f:(fun acc x -> (acc + x) mod mod_base)
;;

let () =
  let _ = input_line stdin in
  let pizzas =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> Array.of_list
  in
  let result = count_pizzas pizzas in
  output_string stdout (string_of_int result ^ "\n")
;;
