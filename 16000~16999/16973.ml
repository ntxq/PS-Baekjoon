open! StdLabels
open! MoreLabels

let prefixSum board =
  let n = Array.length board in
  let m = Array.length board.(0) in
  let prefixBoard = Array.make_matrix ~dimx:n ~dimy:m 0 in

  for i = 0 to n - 1 do
    for j = 0 to m - 1 do
      let a = if i = 0 then 0 else prefixBoard.(i - 1).(j) in
      let b = if j = 0 then 0 else prefixBoard.(i).(j - 1) in
      let c = if i = 0 || j = 0 then 0 else prefixBoard.(i - 1).(j - 1) in
      prefixBoard.(i).(j) <- a + b - c + board.(i).(j)
    done
  done;
  prefixBoard

let bfs board h w sr sc fr fc =
  let n = Array.length board in
  let m = Array.length board.(0) in

  let prefixBoard = prefixSum board in
  let queue = Queue.create () in
  let dist = Array.make_matrix ~dimx:n ~dimy:m Int.max_int in

  Queue.add (sr, sc) queue;
  dist.(sr).(sc) <- 0;

  let isSafe (r, c) =
    0 <= r
    && r + h <= n
    && 0 <= c
    && c + w <= m
    && (prefixBoard.(r + h - 1).(c + w - 1)
       - (if r = 0 then 0 else prefixBoard.(r - 1).(c + w - 1))
       - (if c = 0 then 0 else prefixBoard.(r + h - 1).(c - 1))
       + if r = 0 || c = 0 then 0 else prefixBoard.(r - 1).(c - 1))
       = 0
  in

  let next r c =
    List.filter ~f:isSafe [ (r + 1, c); (r - 1, c); (r, c + 1); (r, c - 1) ]
  in

  let ( let+ ) x f = List.iter ~f x in

  while (not (Queue.is_empty queue)) && dist.(fr).(fc) = Int.max_int do
    let r, c = Queue.take queue in
    let d = dist.(r).(c) in

    let+ nr, nc = next r c in
    if dist.(nr).(nc) = Int.max_int then (
      Queue.add (nr, nc) queue;
      dist.(nr).(nc) <- d + 1)
  done;

  if dist.(fr).(fc) = Int.max_int then -1 else dist.(fr).(fc)

let () =
  let n = input_line stdin |> fun s -> Scanf.sscanf s "%d %d" (fun n _ -> n) in
  let board =
    Array.init n ~f:(fun _ ->
        input_line stdin
        |> String.split_on_char ~sep:' '
        |> List.map ~f:int_of_string |> Array.of_list)
  in
  let h, w, sr, sc, fr, fc =
    input_line stdin |> fun s ->
    Scanf.sscanf s "%d %d %d %d %d %d" (fun h w sr sc fr fc ->
        (h, w, sr - 1, sc - 1, fr - 1, fc - 1))
  in
  bfs board h w sr sc fr fc |> string_of_int |> fun s ->
  output_string stdout (s ^ "\n")
