open! StdLabels
open! MoreLabels

let bfs n s t adj =
  let dist = Array.make_matrix ~dimx:(n + 1) ~dimy:(n + 1) max_int in
  let q = Queue.create () in
  dist.(s).(0) <- 0;
  Queue.add (0, s, 0) q;
  while not (Queue.is_empty q) do
    let d, u, k = Queue.pop q in
    if dist.(u).(k) = d && k < n && u <> t
    then
      List.iter adj.(u) ~f:(fun (v, w) ->
        let d' = d + w in
        if d' < dist.(v).(k + 1)
        then (
          dist.(v).(k + 1) <- d';
          Queue.add (d', v, k + 1) q))
  done;
  dist
;;

let find_min_cost n t dist tax =
  let rec loop i min_cost =
    if i = n
    then min_cost
    else if dist.(t).(i) = max_int
    then loop (i + 1) min_cost
    else loop (i + 1) (min min_cost (dist.(t).(i) + (tax * i)))
  in
  loop 0 max_int
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; m; k ] ->
    (match
       input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
     with
     | [ s; t ] ->
       let adj = Array.make (n + 1) [] in
       for _ = 1 to m do
         match
           input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
         with
         | [ u; v; w ] ->
           adj.(u) <- (v, w) :: adj.(u);
           adj.(v) <- (u, w) :: adj.(v)
         | _ -> ()
       done;
       let taxes = Array.make (k + 1) 0 in
       for i = 1 to k do
         input_line stdin |> int_of_string |> fun x -> taxes.(i) <- taxes.(i - 1) + x
       done;
       let dist = bfs n s t adj in
       Array.map taxes ~f:(fun tax -> find_min_cost n t dist tax)
       |> Array.iter ~f:(fun x ->
         string_of_int x |> output_string stdout;
         output_char stdout '\n')
     | _ -> ())
  | _ -> ()
;;
