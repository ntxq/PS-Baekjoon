open! StdLabels
open! MoreLabels

let find_non_mountains n m =
  (* i: sequence length. j: last number. k: is ascending *)
  let dp = Array.init (n + 1) ~f:(fun _ -> Array.make_matrix ~dimx:(m + 1) ~dimy:2 0L) in
  for j = 1 to m do
    dp.(1).(j).(0) <- 1L
  done;
  for i = 2 to n do
    for j = 1 to m do
      for prev = 1 to j - 1 do
        dp.(i).(j).(1)
        <- Int64.add dp.(i).(j).(1) dp.(i - 1).(prev).(0) |> Int64.add dp.(i - 1).(prev).(1);
        dp.(i).(j).(1) <- Int64.rem dp.(i).(j).(1) 998244353L
      done;
      for prev = j + 1 to m do
        dp.(i).(j).(0) <- Int64.add dp.(i).(j).(0) dp.(i - 1).(prev).(0);
        dp.(i).(j).(0) <- Int64.rem dp.(i).(j).(0) 998244353L
      done;
      dp.(i).(j).(0)
      <- Int64.add dp.(i).(j).(0) dp.(i - 1).(j).(0) |> Int64.add dp.(i - 1).(j).(1);
      dp.(i).(j).(0) <- Int64.rem dp.(i).(j).(0) 998244353L
    done
  done;
  Array.fold_left dp.(n) ~init:0L ~f:(fun acc dp_j ->
    Array.fold_left dp_j ~init:acc ~f:(fun acc dp_j_k ->
      let sum = Int64.add acc dp_j_k in
      Int64.rem sum 998244353L))
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m ] ->
    find_non_mountains n m |> Int64.to_string |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
