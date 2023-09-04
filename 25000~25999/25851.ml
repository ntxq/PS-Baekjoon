open! StdLabels
open! MoreLabels

let count_unique_seq seq =
  let visited = Hashtbl.create (Array.length seq) in
  let rec loop count i j =
    let len = j - i in
    if i = Array.length seq
    then count
    else if j = Array.length seq || Hashtbl.mem visited seq.(j)
    then (
      Hashtbl.remove visited seq.(i);
      loop (count + len) (i + 1) j)
    else (
      Hashtbl.add visited ~key:seq.(j) ~data:();
      loop count i (j + 1))
  in
  loop 0 0 0
;;

let () =
  let _ = input_line stdin in
  input_line stdin
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string
  |> Array.of_list
  |> count_unique_seq
  |> Printf.sprintf "%d\n"
  |> output_string stdout
;;
