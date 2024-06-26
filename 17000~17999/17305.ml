open! StdLabels
open! MoreLabels

let prefix_sum l =
  let sums = Array.of_list l in
  for i = 1 to Array.length sums - 1 do
    sums.(i) <- sums.(i - 1) + sums.(i)
  done;
  sums
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; w ] ->
    let rec loop idx acc3 acc5 =
      if idx = n
      then (
        let rev_sort l = List.fast_sort ~cmp:(fun a b -> compare b a) l in
        rev_sort acc3, rev_sort acc5)
      else (
        match
          input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
        with
        | [ 3; s ] -> loop (idx + 1) (s :: acc3) acc5
        | [ 5; s ] -> loop (idx + 1) acc3 (s :: acc5)
        | _ -> assert false)
    in
    let candy3, candy5 = loop 0 [] [] in
    let candy3_sum = prefix_sum candy3 in
    let candy5_sum = prefix_sum candy5 in
    let rec loop idx acc =
      if idx * 3 > w
      then acc
      else (
        let candy3_count = min idx (Array.length candy3_sum) in
        let candy5_count = min ((w - (idx * 3)) / 5) (Array.length candy5_sum) in
        let cur_sum =
          (if candy3_count = 0 then 0 else candy3_sum.(candy3_count - 1))
          + if candy5_count = 0 then 0 else candy5_sum.(candy5_count - 1)
        in
        loop (idx + 1) (max acc cur_sum))
    in
    loop 0 0 |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
