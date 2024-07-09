open! StdLabels
open! MoreLabels

let find_start m board =
  let rec loop i j =
    if j = m then loop (i + 1) 0 else if board.(i).[j] = 'I' then i, j else loop i (j + 1)
  in
  loop 0 0
;;

let bfs sx sy n m board =
  let q = Queue.create () in
  let visited = Array.make_matrix ~dimx:n ~dimy:m false in
  Queue.push (sx, sy) q;
  visited.(sx).(sy) <- true;
  let d = [ 0, 1; 0, -1; 1, 0; -1, 0 ] in
  let rec loop count =
    if Queue.is_empty q
    then count
    else (
      let x, y = Queue.pop q in
      List.iter d ~f:(fun (dx, dy) ->
        let nx = x + dx in
        let ny = y + dy in
        if 0 <= nx
           && nx < n
           && 0 <= ny
           && ny < m
           && (not visited.(nx).(ny))
           && board.(nx).[ny] != 'X'
        then (
          visited.(nx).(ny) <- true;
          Queue.push (nx, ny) q);
        ());
      loop (count + if board.(x).[y] = 'P' then 1 else 0))
  in
  loop 0
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m ] ->
    let board = Array.init n ~f:(fun _ -> input_line stdin) in
    let sx, sy = find_start m board in
    (match bfs sx sy n m board with
     | 0 -> output_string stdout "TT\n"
     | count ->
       string_of_int count |> output_string stdout;
       output_char stdout '\n')
  | _ -> ()
;;
