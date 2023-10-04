open! StdLabels
open! MoreLabels

let bfs board =
  let visited =
    let m = Array.length board in
    Array.make_matrix ~dimx:m ~dimy:m Int.max_int
  in
  let q = Queue.create () in
  let dist = ref (-1) in
  visited.(0).(0) <- 0;
  Queue.push (0, 0) q;
  let dxy = [ 1, 0; -1, 0; 0, 1; 0, -1 ] in
  let is_safe x y =
    0 <= x
    && x < Array.length board
    && 0 <= y
    && y < Array.length board
    && (board.(x).(y) = '-' || board.(x).(y) = 'd')
  in
  while not (Queue.is_empty q) do
    let x, y = Queue.pop q in
    List.iter dxy ~f:(fun (dx, dy) ->
      let nx = x + dx in
      let ny = y + dy in
      if is_safe nx ny && visited.(x).(y) + 1 < visited.(nx).(ny)
      then (
        visited.(nx).(ny) <- visited.(x).(y) + 1;
        Queue.push (nx, ny) q;
        if board.(nx).(ny) = 'd' then dist := visited.(nx).(ny)))
  done;
  !dist
;;

let () =
  let t = input_line stdin |> int_of_string in
  for _ = 1 to t do
    let m = input_line stdin |> int_of_string in
    let board = Array.make_matrix ~dimx:m ~dimy:m ' ' in
    for i = 0 to m - 1 do
      input_line stdin |> String.iteri ~f:(fun j c -> board.(i).(j) <- c)
    done;
    bfs board |> Printf.sprintf "%d\n" |> output_string stdout
  done
;;
