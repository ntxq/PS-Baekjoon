open! StdLabels
open! MoreLabels

let merge_nums nums =
  let rec loop nums stack output =
    match nums, stack with
    | _, (minA, maxA, idxA) :: (minB, maxB, idxB) :: restStack when maxA + 1 = minB ->
      loop nums ((minA, maxB, idxA) :: restStack) (idxB :: output)
    | _, (minA, maxA, idxA) :: (minB, maxB, idxB) :: restStack when minA - 1 = maxB ->
      loop nums ((minB, maxA, idxA) :: restStack) (idxB :: output)
    | (n, idx) :: ns, [] -> loop ns [ n, n, idx ] output
    | (n, idx) :: ns, (minN, maxN, lastIdx) :: restStack ->
      if n = minN - 1
      then loop ns ((n, maxN, idx) :: restStack) (lastIdx :: output)
      else if n = maxN + 1
      then loop ns ((minN, n, idx) :: restStack) (lastIdx :: output)
      else loop ns ((n, n, idx) :: stack) output
    | [], _ -> List.rev output
  in
  loop (List.mapi ~f:(fun i n -> n, i + 1) nums) [] []
;;

let () =
  let _ = input_line stdin in
  let nums =
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  in
  merge_nums nums
  |> List.map ~f:string_of_int
  |> String.concat ~sep:"\n"
  |> output_string stdout;
  output_char stdout '\n'
;;
