open! StdLabels
open! MoreLabels

let bfs n m board =
  let queue = Queue.create () in
  let dist =
    Array.init n ~f:(fun _ ->
        Array.init m ~f:(fun _ -> Array.make_matrix ~dimx:4 ~dimy:3 Int.max_int))
  in

  let next x y d =
    [ (x + 1, y, 0); (x - 1, y, 1); (x, y + 1, 2); (x, y - 1, 3) ]
    |> List.filter ~f:(fun (nx, ny, nd) ->
           0 <= nx && nx < n && 0 <= ny && ny < m && d <> nd
           && board.(nx).(ny) <> '#')
  in

  Array.iteri board ~f:(fun x row ->
      Array.iteri row ~f:(fun y cell ->
          if cell = 'S' then
            [ 0; 1; 2; 3 ]
            |> List.iter ~f:(fun d ->
                   Queue.add (x, y, d, 0) queue;
                   dist.(x).(y).(d).(0) <- 0)));

  let rec find_target x y ch =
    if y = m then find_target (x + 1) 0 ch
    else if x = n then ()
    else if board.(x).(y) = 'C' then (
      board.(x).(y) <- ch;
      find_target x (y + 1) 'Y')
    else find_target x (y + 1) ch
  in
  find_target 0 0 'X';

  let ( let+ ) x f = List.iter x ~f in
  let minDist = ref Int.max_int in
  while (not (Queue.is_empty queue)) && !minDist = Int.max_int do
    let x, y, d, t = Queue.take queue in

    let+ nx, ny, nd = next x y d in
    let nt =
      if board.(nx).(ny) = 'X' then t lor 2
      else if board.(nx).(ny) = 'Y' then t lor 1
      else t
    in
    if nt = 3 then minDist := dist.(x).(y).(d).(t) + 1
    else if dist.(nx).(ny).(nd).(nt) > dist.(x).(y).(d).(t) + 1 then (
      dist.(nx).(ny).(nd).(nt) <- dist.(x).(y).(d).(t) + 1;
      Queue.add (nx, ny, nd, nt) queue)
  done;

  if !minDist = Int.max_int then -1 else !minDist

let () =
  let n, m =
    input_line stdin |> fun s -> Scanf.sscanf s "%d %d" (fun x y -> (x, y))
  in
  let board =
    Array.init n ~f:(fun _ -> input_line stdin |> String.to_seq |> Array.of_seq)
  in
  bfs n m board |> Int.to_string |> fun s -> output_string stdout (s ^ "\n")
