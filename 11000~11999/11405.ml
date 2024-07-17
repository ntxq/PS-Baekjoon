open! StdLabels
open! MoreLabels

let shortest_path s n adj cost capacity =
  let dist = Array.make n max_int in
  let parent = Array.make n (-1) in
  let in_queue = Array.make n false in
  let q = Queue.create () in
  dist.(s) <- 0;
  in_queue.(s) <- true;
  Queue.push s q;
  while not (Queue.is_empty q) do
    let u = Queue.pop q in
    in_queue.(u) <- false;
    List.iter adj.(u) ~f:(fun v ->
      if capacity.(u).(v) > 0 && dist.(v) > dist.(u) + cost.(u).(v)
      then (
        dist.(v) <- dist.(u) + cost.(u).(v);
        parent.(v) <- u;
        if not in_queue.(v)
        then (
          Queue.push v q;
          in_queue.(v) <- true)))
  done;
  dist, parent
;;

let find_min_flow s t parent capacity =
  let rec loop cur min_flow =
    if cur = s
    then min_flow
    else (
      let u = parent.(cur) in
      let min_flow = min min_flow capacity.(u).(cur) in
      loop u min_flow)
  in
  loop t max_int
;;

let apply_flow s t f parent capacity =
  let rec loop cur =
    if cur = s
    then ()
    else (
      let u = parent.(cur) in
      capacity.(u).(cur) <- capacity.(u).(cur) - f;
      capacity.(cur).(u) <- capacity.(cur).(u) + f;
      loop u)
  in
  loop t
;;

let min_cost_flow n adj cost capacity s t =
  let rec loop cur_cost =
    let dist, parent = shortest_path s n adj cost capacity in
    if dist.(t) = max_int
    then cur_cost
    else (
      let f = find_min_flow s t parent capacity in
      let cost' = cur_cost + (dist.(t) * f) in
      apply_flow s t f parent capacity;
      loop cost')
  in
  loop 0
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m ] ->
    let adj = Array.make (n + m + 2) [] in
    let cost = Array.make_matrix ~dimx:(n + m + 2) ~dimy:(n + m + 2) 0 in
    let capacity = Array.make_matrix ~dimx:(n + m + 2) ~dimy:(n + m + 2) 0 in
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> List.iteri ~f:(fun i x ->
      adj.(0) <- (i + 1) :: adj.(0);
      adj.(i + 1) <- 0 :: adj.(i + 1);
      capacity.(0).(i + 1) <- x);
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> List.iteri ~f:(fun j x ->
      for i = 1 to n do
        adj.(i) <- (n + j + 1) :: adj.(i);
        adj.(n + j + 1) <- i :: adj.(n + j + 1);
        capacity.(i).(n + j + 1) <- max_int
      done;
      adj.(n + j + 1) <- (n + m + 1) :: adj.(n + j + 1);
      adj.(n + m + 1) <- (n + j + 1) :: adj.(n + m + 1);
      capacity.(n + j + 1).(n + m + 1) <- x);
    for i = 1 to m do
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> List.iteri ~f:(fun j x ->
        cost.(j + 1).(n + i) <- x;
        cost.(n + i).(j + 1) <- -x)
    done;
    min_cost_flow (n + m + 2) adj cost capacity 0 (n + m + 1)
    |> string_of_int
    |> output_string stdout;
    output_char stdout '\n'
  | _ -> ()
;;
