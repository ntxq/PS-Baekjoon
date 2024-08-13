open! StdLabels
open! MoreLabels

let binary_search nums x =
  let rec loop l r =
    if l >= r
    then l
    else (
      let m = (l + r) / 2 in
      if x <= nums.(m) then loop l m else loop (m + 1) r)
  in
  let l = loop 0 (Array.length nums - 1) in
  if nums.(l) = x then l else -1
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m ] ->
    let nums = Array.init n ~f:(fun _ -> input_line stdin |> int_of_string) in
    Array.fast_sort nums ~cmp:Int.compare;
    List.init ~len:m ~f:(fun _ -> input_line stdin |> int_of_string |> binary_search nums)
    |> List.iter ~f:(fun x ->
      string_of_int x |> output_string stdout;
      output_char stdout '\n')
  | _ -> ()
;;
