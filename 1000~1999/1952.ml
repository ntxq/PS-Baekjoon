open! StdLabels
open! MoreLabels

let make_turn dx dy =
  match dx, dy with
  | 0, 1 -> 1, 0
  | 1, 0 -> 0, -1
  | 0, -1 -> -1, 0
  | -1, 0 -> 0, 1
  | _ -> assert false
;;

let count_turns n m =
  let snail = Array.make_matrix ~dimx:n ~dimy:m false in
  let cnt = ref (n * m) in
  let x = ref 0 in
  let y = ref (-1) in
  let rec draw_line dx dy =
    x := !x + dx;
    y := !y + dy;
    snail.(!x).(!y) <- true;
    decr cnt;
    if 0 <= !x + dx
       && !x + dx < n
       && 0 <= !y + dy
       && !y + dy < m
       && not snail.(!x + dx).(!y + dy)
    then draw_line dx dy
  in
  let dx = ref 0 in
  let dy = ref 1 in
  let turns = ref 0 in
  while !cnt > 0 do
    draw_line !dx !dy;
    incr turns;
    let dx', dy' = make_turn !dx !dy in
    dx := dx';
    dy := dy'
  done;
  !turns - 1
;;

let () =
  let n, m = input_line stdin |> fun str -> Scanf.sscanf str "%d %d" (fun n m -> n, m) in
  let cnt = count_turns n m in
  string_of_int cnt |> output_string stdout;
  output_string stdout "\n"
;;
