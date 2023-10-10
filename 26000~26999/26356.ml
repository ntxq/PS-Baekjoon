open! StdLabels
open! MoreLabels

let bfs n sx sy tx ty =
  let dist = Array.make_matrix ~dimx:n ~dimy:n Int.max_int in
  let q = Queue.create () in
  dist.(sx - 1).(sy - 1) <- 0;
  Queue.push (sx - 1, sy - 1) q;
  let mv = [ -2, -1; -2, 1; -1, -2; -1, 2; 1, -2; 1, 2; 2, -1; 2, 1 ] in
  let is_safe x y = 0 <= x && x < n && 0 <= y && y < n in
  while not (Queue.is_empty q) do
    let x, y = Queue.pop q in
    List.iter mv ~f:(fun (dx, dy) ->
      let nx = x + dx in
      let ny = y + dy in
      if is_safe nx ny && dist.(x).(y) + 1 < dist.(nx).(ny)
      then (
        dist.(nx).(ny) <- dist.(x).(y) + 1;
        Queue.push (nx, ny) q))
  done;
  dist.(tx - 1).(ty - 1)
;;

let () =
  let t = input_line stdin |> int_of_string in
  for i = 1 to t do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ n; sx; sy; tx; ty ] ->
      bfs n sx sy tx ty |> Printf.sprintf "Case #%d: %d\n\n" i |> output_string stdout
    | _ -> assert false
  done
;;
