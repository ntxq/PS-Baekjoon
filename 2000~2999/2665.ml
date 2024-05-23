(* open! Core *)
open! StdLabels
open! MoreLabels

let bfs n board =
  let visited = Array.make_matrix ~dimx:n ~dimy:n false in
  let front_queue = Queue.create () in
  let back_queue = Queue.create () in
  visited.(0).(0) <- true;
  Queue.add (0, 0) front_queue;
  let rec loop dist front back =
    if visited.(n - 1).(n - 1)
    then dist
    else if Queue.is_empty front
    then loop (dist + 1) back front 
    else (
      let x, y = Queue.pop front in
      let nexts = [ x + 1, y; x - 1, y; x, y + 1; x, y - 1 ] in
      List.filter nexts ~f:(fun (nx, ny) ->
        0 <= nx && nx < n && 0 <= ny && ny < n && not visited.(nx).(ny))
      |> List.iter ~f:(fun (nx, ny) ->
        visited.(nx).(ny) <- true;
        if board.(nx).(ny) = '1'
        then Queue.add (nx, ny) front
        else Queue.add (nx, ny) back);
      loop dist front back)
  in
  loop 0 front_queue back_queue
;;

let () =
  let n = input_line stdin |> int_of_string in
  let board =
    Array.init n ~f:(fun _ -> input_line stdin |> String.to_seq |> Array.of_seq)
  in
  bfs n board |> string_of_int |> output_string stdout;
  output_char stdout '\n'
;;
