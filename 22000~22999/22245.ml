open! StdLabels
open! MoreLabels

let find_max_boats boats =
  let sorted_boats = List.sort boats ~cmp:(fun (_, p1) (_, p2) -> compare p1 p2) in
  let rec loop (l, r) count boats =
    match boats with
    | [] -> count
    | (len, ring) :: rest ->
      if ring >= r
      then (
        let left = max r (ring - len) in
        let right = left + len in
        loop (left, right) (count + 1) rest)
      else if len < r - l
      then (
        let left = max l (ring - len) in
        let right = left + len in
        loop (left, right) count rest)
      else loop (l, r) count rest
  in
  loop (-200000, -200000) 0 sorted_boats
;;

let () =
  let n = input_line stdin |> int_of_string in
  let boats =
    let rec loop i acc =
      if i = n
      then acc
      else (
        match
          input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
        with
        | [ l; p ] -> loop (i + 1) ((l, p) :: acc)
        | _ -> assert false)
    in
    loop 0 []
  in
  find_max_boats boats |> Printf.sprintf "%d\n" |> output_string stdout
;;
