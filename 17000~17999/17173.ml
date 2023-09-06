open! StdLabels
open! MoreLabels

let () =
  let multiples = Hashtbl.create 1000000 in
  let add_multiples n k =
    let rec loop i =
      if k * i <= n
      then (
        Hashtbl.add multiples ~key:(k * i) ~data:();
        loop (i + 1))
    in
    loop 1
  in
  let n = input_line stdin |> String.split_on_char ~sep:' ' |> List.hd |> int_of_string in
  input_line stdin
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string
  |> List.iter ~f:(add_multiples n);
  List.init ~len:(n + 1) ~f:Fun.id
  |> List.fold_left ~init:0 ~f:(fun acc i ->
    if Hashtbl.mem multiples i then acc + i else acc)
  |> Printf.sprintf "%d\n"
  |> output_string stdout
;;
