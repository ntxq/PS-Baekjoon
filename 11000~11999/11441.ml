open! StdLabels
open! MoreLabels

let get_prefix_sums numbers =
  let prefix_sum = Array.make (Array.length numbers + 1) 0 in
  Array.iteri numbers ~f:(fun i number -> prefix_sum.(i + 1) <- prefix_sum.(i) + number);
  fun i j -> prefix_sum.(j) - prefix_sum.(i - 1)
;;

let () =
  let _ = input_line stdin in
  let get_range =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> Array.of_list
    |> get_prefix_sums
  in
  let m = input_line stdin |> int_of_string in
  for _ = 1 to m do
    let i, j =
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ i; j ] -> i, j
      | _ -> assert false
    in
    get_range i j |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  done
;;
