open! StdLabels
open! MoreLabels

let binary_search total_speed boxes =
  let open Int64 in
  let left = 1L in
  let right = div boxes total_speed |> mul 2L in
  let rec loop left right =
    if left >= right
    then left
    else (
      let mid = div (add left right) 2L in
      let cur_boxes = mul total_speed mid in
      if cur_boxes >= boxes then loop left mid else loop (succ mid) right)
  in
  loop left right
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:Int64.of_string
  with
  | [ n; k ] ->
    let speeds =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:Int64.of_string
      |> List.fast_sort ~cmp:Int64.compare
    in
    let team1_speed = List.hd speeds in
    let rec loop idx speeds acc =
      match speeds with
      | [] -> acc
      | cur_speed :: rest ->
        let open Int64 in
        let team1 = mul team1_speed idx in
        let team2 = sub n idx |> mul cur_speed in
        binary_search (add team1 team2) k |> Stdlib.min acc |> loop (succ idx) rest
    in
    loop 1L (List.tl speeds) Int64.max_int |> Int64.to_string |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
