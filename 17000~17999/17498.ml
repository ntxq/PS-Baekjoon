(* open! Core *)
open! StdLabels

let solve n m d dp board =
  Array.fill dp ~pos:0 ~len:m Int32.zero;
  for cur_x = 0 to n - 1 do
    for cur_y = 0 to m - 1 do
      let cur_board = board.(cur_x).(cur_y) in
      let cur_score = dp.((cur_x * m) + cur_y) in
      for next_x = cur_x + 1 to min (cur_x + d) (n - 1) do
        let remain_dist = d - (next_x - cur_x) in
        for next_y = max (cur_y - remain_dist) 0 to min (cur_y + remain_dist) (m - 1) do
          let next_board = board.(next_x).(next_y) in
          let next_score = Int32.mul cur_board next_board |> Int32.add cur_score in
          dp.((next_x * m) + next_y) <- max dp.((next_x * m) + next_y) next_score
        done
      done
    done
  done;
  let max_score = ref Int32.min_int in
  for j = 0 to m - 1 do
    max_score := max !max_score dp.(((n - 1) * m) + j)
  done;
  !max_score
;;

let () =
  Gc.set { (Gc.get ()) with max_overhead = 10000; allocation_policy = 2 };
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m; d ] ->
    let dp = Array.make (n * m) Int32.min_int in
    let board = Array.init n ~f:(fun _ -> Array.make m Int32.zero) in
    for i = 0 to n - 1 do
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:Int32.of_string
      |> List.iteri ~f:(fun j x -> board.(i).(j) <- x)
    done;
    solve n m d dp board |> Int32.to_string |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
