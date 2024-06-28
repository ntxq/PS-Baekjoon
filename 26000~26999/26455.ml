open! StdLabels
open! MoreLabels

let () =
  let n = input_line stdin |> int_of_string in
  let pizzas =
    Array.init n ~f:(fun _ ->
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ t; a ] -> t, a
      | _ -> assert false)
  in
  Array.fast_sort pizzas ~cmp:(fun (t1, a1) (t2, a2) ->
    let v1 = float_of_int a1 /. ((2. *. float_of_int t1) +. 1.) in
    let v2 = float_of_int a2 /. ((2. *. float_of_int t2) +. 1.) in
    compare v2 v1);
  let rec loop idx time acc =
    if idx = n
    then acc
    else (
      let t, a = pizzas.(idx) in
      let cur_acc = acc + (a * (time + t + idx)) in
      loop (idx + 1) (time + (2 * t)) cur_acc)
  in
  loop 0 0 0 |> string_of_int |> output_string stdout;
  output_char stdout '\n'
;;
