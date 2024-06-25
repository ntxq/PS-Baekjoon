open! StdLabels
open! MoreLabels

let table = Array.init 100000 ~f:(fun i -> (i * i))

let () =
  let diff = input_line stdin |> int_of_string in
  let rec loop i j acc =
    if i = 100000 || j = 100000
    then List.rev acc
    else (
      let cur_diff = table.(i) - table.(j) in
      match Int.compare cur_diff diff with
      | -1 -> loop (i + 1) j acc
      | 0 -> loop (i + 1) (j + 1) (i :: acc)
      | 1 -> loop i (j + 1) acc
      | _ -> assert false)
  in
  match loop 1 1 [] with
  | [] -> output_string stdout "-1\n"
  | l -> List.iter l ~f:(fun l -> output_string stdout (string_of_int l ^ "\n"))
;;
