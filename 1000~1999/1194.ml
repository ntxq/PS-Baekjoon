open! StdLabels
open! MoreLabels

let filter_bounds board (x, y) =
  0 <= x && x < Array.length board && 0 <= y && y < Array.length board.(0)

let filter_visited visited keys (x, y) = visited.(x).(y) land keys <> keys

let bfs board (sx, sy) =
  let visited =
    Array.make_matrix ~dimx:(Array.length board)
      ~dimy:(Array.length board.(0))
      0
  in
  let q = Queue.create () in

  Queue.push (sx, sy, 0, 1) q;
  visited.(sx).(sy) <- 1;

  let min_dist = ref (-1) in
  while (not (Queue.is_empty q)) && !min_dist = -1 do
    let ux, uy, cur_dist, cur_keys = Queue.pop q in
    let next_pos = [ (ux, uy + 1); (ux, uy - 1); (ux + 1, uy); (ux - 1, uy) ] in
    List.filter ~f:(filter_bounds board) next_pos
    |> List.filter ~f:(filter_visited visited cur_keys)
    |> List.iter ~f:(fun (nx, ny) ->
           match board.(nx).(ny) with
           | '.' | '0' ->
               visited.(nx).(ny) <- cur_keys;
               Queue.push (nx, ny, cur_dist + 1, cur_keys) q
           | 'a' .. 'z' ->
               let key =
                 Char.code board.(nx).(ny) - Char.code 'a' |> fun x -> 2 lsl x
               in
               let new_keys = cur_keys lor key in
               visited.(nx).(ny) <- new_keys;
               Queue.push (nx, ny, cur_dist + 1, new_keys) q
           | 'A' .. 'Z' ->
               let has_key =
                 Char.code board.(nx).(ny) - Char.code 'A'
                 |> (fun x -> 2 lsl x)
                 |> Int.logand cur_keys
                 |> function
                 | 0 -> false
                 | _ -> true
               in
               if has_key then (
                 visited.(nx).(ny) <- cur_keys;
                 Queue.push (nx, ny, cur_dist + 1, cur_keys) q)
           | '1' -> min_dist := cur_dist + 1
           | _ -> ())
  done;
  !min_dist

let () =
  let n, _ =
    read_line () |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    |> fun xs -> (List.nth xs 0, List.nth xs 1)
  in
  let board =
    Array.init n ~f:(fun _ -> read_line () |> String.to_seq |> Array.of_seq)
  in
  let start =
    Array.mapi board ~f:(fun i row ->
        (i, Array.mapi row ~f:(fun j c -> (j, c))))
    |> Array.fold_left ~init:None ~f:(fun acc (i, row) ->
           match acc with
           | Some _ -> acc
           | None ->
               Array.fold_left row ~init:None ~f:(fun acc (j, c) ->
                   match acc with
                   | Some _ -> acc
                   | None -> if c = '0' then Some (i, j) else None))
    |> Option.get
  in
  bfs board start |> Printf.printf "%d\n"
