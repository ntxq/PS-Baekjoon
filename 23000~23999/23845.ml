open! StdLabels
open! MoreLabels

let rec read_input n acc =
  match input_line stdin with
  | exception End_of_file -> []
  | line ->
    let input = String.split_on_char ~sep:' ' line |> List.map ~f:int_of_string in
    let len = List.length input in
    if len = n then input @ acc else read_input (n - len) (input @ acc)
;;

let () =
  let n = input_line stdin |> int_of_string in
  let dolls = read_input n [] |> List.fast_sort ~cmp:(fun a b -> b - a) in
  let qs = Array.init 10002 ~f:(fun _ -> Queue.create ()) in
  let rec loop dolls =
    match dolls with
    | [] -> ()
    | doll :: rest ->
      if Queue.is_empty qs.(doll + 1)
      then Queue.push doll qs.(doll)
      else Queue.push (Queue.pop qs.(doll + 1)) qs.(doll);
      loop rest
  in
  loop dolls;
  Array.mapi qs ~f:(fun i q ->
    Queue.fold
      (fun acc max_size ->
        Int64.add
          acc
          (Int64.mul (Int64.of_int max_size) (Int64.of_int (max_size - i + 1))))
      0L
      q)
  |> Array.fold_left ~f:Int64.add ~init:0L
  |> Int64.to_string
  |> output_string stdout;
  output_char stdout '\n'
;;
