open! StdLabels
open! MoreLabels

let bfs board (sx, sy) limit =
  let queue = Queue.create () in
  let visited =
    Array.make_matrix ~dimx:(Array.length board)
      ~dimy:(Array.length board.(0))
      false
  in

  Queue.add (sx - 1, sy, 1) queue;
  visited.(sx - 1).(sy) <- true;
  let target = ref None in

  while (not (Queue.is_empty queue)) && !target = None do
    let x, y, d = Queue.pop queue in
    if board.(x).(y) then target := Some (x, y)
    else if d < limit then
      let neighbors = [ (x, y - 1); (x - 1, y); (x, y + 1) ] in
      List.iter neighbors ~f:(fun (x, y) ->
          if
            0 <= x
            && x < Array.length board
            && 0 <= y
            && y < Array.length board.(0)
            && not visited.(x).(y)
          then (
            Queue.add (x, y, d + 1) queue;
            visited.(x).(y) <- true))
  done;
  !target

let fire_arrow board hunters limit =
  List.map hunters ~f:(fun (x, y) -> bfs board (x, y) limit)
  |> List.fold_left ~init:0 ~f:(fun acc -> function
       | None -> acc
       | Some (x, y) ->
           if board.(x).(y) then (
             board.(x).(y) <- false;
             acc + 1)
           else acc)

let move_enemy board =
  Array.init (Array.length board) ~f:(fun i ->
      if i > 0 then board.(i - 1) else Array.make (Array.length board.(0)) false)

let is_over board =
  Array.for_all board ~f:(fun row ->
      Array.for_all row ~f:(fun cell -> not cell))

let rec run board hunters limit score =
  if is_over board then score
  else
    let new_score = score + fire_arrow board hunters limit in
    let new_board = move_enemy board in
    run new_board hunters limit new_score

let possible_hunters n m =
  let make i j k = [ (n, i); (n, j); (n, k) ] in
  let rec loop i j k acc =
    if i = m then acc
    else if j = m then loop (i + 1) (i + 2) (i + 3) acc
    else if k = m then loop i (j + 1) (j + 2) acc
    else loop i j (k + 1) (make i j k :: acc)
  in
  loop 0 1 2 []

let solve board limit =
  let n = Array.length board in
  let m = Array.length board.(0) in
  possible_hunters n m
  |> List.fold_left ~init:0 ~f:(fun acc hunters ->
         let new_board = Array.map board ~f:Array.copy |> Array.copy in
         max acc (run new_board hunters limit 0))

let () =
  let n, _, limit =
    read_line () |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    |> function
    | [ n; m; limit ] -> (n, m, limit)
    | _ -> assert false
  in
  let board =
    Array.init n ~f:(fun _ ->
        read_line ()
        |> String.split_on_char ~sep:' '
        |> List.map ~f:(function
             | "0" -> false
             | "1" -> true
             | _ -> assert false)
        |> Array.of_list)
  in
  solve board limit |> string_of_int |> print_endline
