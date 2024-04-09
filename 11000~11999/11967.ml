(* open! Core *)
open! StdLabels
open! MoreLabels

let is_rechable x y n visited =
  [ x - 1, y; x + 1, y; x, y - 1; x, y + 1 ]
  |> List.exists ~f:(fun (x, y) -> 0 <= x && x < n && 0 <= y && y < n && visited.(x).(y))
;;

let bfs n lights =
  let q = Queue.create () in
  let visited = Array.make_matrix ~dimx:n ~dimy:n false in
  let edges = Array.make_matrix ~dimx:n ~dimy:n [] in
  let switched = Array.make_matrix ~dimx:n ~dimy:n false in
  Queue.push (0, 0) q;
  visited.(0).(0) <- true;
  switched.(0).(0) <- true;
  while not (Queue.is_empty q) do
    let sx, sy = Queue.pop q in
    List.iter
      lights.(sx).(sy)
      ~f:(fun (tx, ty) ->
        match visited.(tx).(ty), is_rechable tx ty n visited with
        | false, true ->
          visited.(tx).(ty) <- true;
          Queue.push (tx, ty) q
        | false, false ->
          [ tx - 1, ty; tx + 1, ty; tx, ty - 1; tx, ty + 1 ]
          |> List.filter ~f:(fun (x, y) -> 0 <= x && x < n && 0 <= y && y < n)
          |> List.iter ~f:(fun (x, y) -> edges.(x).(y) <- (tx, ty) :: edges.(x).(y))
        | _ -> ());
    List.iter
      lights.(sx).(sy)
      ~f:(fun (tx, ty) -> if not switched.(tx).(ty) then switched.(tx).(ty) <- true);
    List.iter
      edges.(sx).(sy)
      ~f:(fun (tx, ty) ->
        if not visited.(tx).(ty)
        then (
          visited.(tx).(ty) <- true;
          Queue.push (tx, ty) q))
  done;
  Array.fold_left switched ~init:0 ~f:(fun acc row ->
    acc + Array.fold_left row ~init:0 ~f:(fun acc b -> if b then acc + 1 else acc))
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m ] ->
    let lights = Array.make_matrix ~dimx:n ~dimy:n [] in
    for _ = 1 to m do
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ a; b; c; d ] ->
        lights.(a - 1).(b - 1) <- (c - 1, d - 1) :: lights.(a - 1).(b - 1)
      | _ -> assert false
    done;
    bfs n lights |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
