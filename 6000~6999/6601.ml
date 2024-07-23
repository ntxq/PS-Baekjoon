open! StdLabels
open! MoreLabels

let bfs sx sy tx ty =
  let queue = Queue.create () in
  let dist = Array.make_matrix ~dimx:8 ~dimy:8 (-1) in
  let dx = [| 2; 2; -2; -2; 1; 1; -1; -1 |] in
  let dy = [| 1; -1; 1; -1; 2; -2; 2; -2 |] in
  Queue.add (sx, sy) queue;
  dist.(sx).(sy) <- 0;
  while (not (Queue.is_empty queue)) && dist.(tx).(ty) = -1 do
    let x, y = Queue.pop queue in
    for i = 0 to 7 do
      let nx = x + dx.(i) in
      let ny = y + dy.(i) in
      if 0 <= nx && nx < 8 && 0 <= ny && ny < 8 && dist.(nx).(ny) = -1
      then (
        Queue.push (nx, ny) queue;
        dist.(nx).(ny) <- dist.(x).(y) + 1)
    done
  done;
  dist.(tx).(ty)
;;

let () =
  let rec loop () =
    match input_line stdin with
    | exception End_of_file -> ()
    | line ->
      let sx, sy, tx, ty =
        Scanf.sscanf line "%c%d %c%d" (fun a b c d ->
          Char.code a - 97, b - 1, Char.code c - 97, d - 1)
      in
      bfs sx sy tx ty
      |> Printf.sprintf
           "To get from %c%d to %c%d takes %d knight moves.\n"
           (Char.chr (sx + 97))
           (sy + 1)
           (Char.chr (tx + 97))
           (ty + 1)
      |> output_string stdout;
      loop ()
  in
  loop ()
;;
