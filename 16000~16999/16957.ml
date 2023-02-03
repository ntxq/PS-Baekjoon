open! StdLabels
open! MoreLabels

let run board r c =
  let balls = Array.make_matrix ~dimx:r ~dimy:c 0 in
  let dp = Array.make_matrix ~dimx:r ~dimy:c (-1, -1) in

  let rec dfs i j balls dp =
    if dp.(i).(j) <> (-1, -1) then (
      let x, y = dp.(i).(j) in
      balls.(x).(y) <- balls.(x).(y) + 1;
      dp.(i).(j))
    else
      let dx = [ -1; 0; 1 ] in
      let dy = [ -1; 0; 1 ] in
      let neighbors =
        List.concat_map dx ~f:(fun x ->
            List.map dy ~f:(fun y -> (i + x, j + y)))
      in
      let minCoord =
        List.filter neighbors ~f:(fun (x, y) ->
            x >= 0 && x < r && y >= 0 && y < c)
        |> List.fold_left ~init:(i, j) ~f:(fun (x1, y1) (x2, y2) ->
               if board.(x1).(y1) > board.(x2).(y2) then (x2, y2) else (x1, y1))
      in
      if minCoord = (i, j) then (
        balls.(i).(j) <- balls.(i).(j) + 1;
        dp.(i).(j) <- (i, j);
        dp.(i).(j))
      else
        let mi, mj = minCoord in
        dp.(i).(j) <- dfs mi mj balls dp;
        dp.(i).(j)
  in

  let rec loop i j balls dp =
    if i = r then balls
    else if j = c then loop (i + 1) 0 balls dp
    else (
      ignore (dfs i j balls dp : int * int);
      loop i (j + 1) balls dp)
  in

  loop 0 0 balls dp

let () =
  let r, c =
    input_line stdin |> fun s -> Scanf.sscanf s "%d %d" (fun r c -> (r, c))
  in
  let board =
    Array.init r ~f:(fun _ ->
        input_line stdin
        |> String.split_on_char ~sep:' '
        |> List.map ~f:int_of_string |> Array.of_list)
  in
  let result = run board r c in

  Array.iter result ~f:(fun row ->
      Array.iter row ~f:(fun x ->
          Printf.sprintf "%d " x |> output_string stdout);
      output_string stdout "\n")
