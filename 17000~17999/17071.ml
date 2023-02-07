open! StdLabels
open! MoreLabels

let bfs s t =
  let q = Queue.create () in
  let visitedEven = Array.make 500001 max_int in
  let visitedOdd = Array.make 500001 max_int in

  Queue.add (s, true) q;
  visitedEven.(s) <- 0;

  while not (Queue.is_empty q) do
    let u, isEven = Queue.take q in
    let curDist = if isEven then visitedEven.(u) else visitedOdd.(u) in
    let visited = if isEven then visitedOdd else visitedEven in

    if u > 0 && curDist + 1 < visited.(u - 1) then (
      Queue.add (u - 1, not isEven) q;
      visited.(u - 1) <- curDist + 1);

    if u < 500000 && curDist + 1 < visited.(u + 1) then (
      Queue.add (u + 1, not isEven) q;
      visited.(u + 1) <- curDist + 1);

    if u * 2 < 500001 && curDist + 1 < visited.(u * 2) then (
      Queue.add (u * 2, not isEven) q;
      visited.(u * 2) <- curDist + 1)
  done;

  let rec loop idx curTime =
    if idx > 500000 then -1
    else if curTime mod 2 = 0 && visitedEven.(idx) <= curTime then curTime
    else if curTime mod 2 = 1 && visitedOdd.(idx) <= curTime then curTime
    else loop (idx + curTime + 1) (curTime + 1)
  in

  loop t 0

let () =
  let s, t =
    input_line stdin |> fun s -> Scanf.sscanf s "%d %d" (fun s t -> (s, t))
  in

  Printf.sprintf "%d\n" (bfs s t) |> output_string stdout
