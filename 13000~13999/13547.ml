open! StdLabels
open! MoreLabels

let compare_query k (s1, e1) (s2, e2) =
  let b1 = s1 / k in
  let b2 = s2 / k in
  if b1 = b2 then e1 - e2 else b1 - b2

let solve sequence queries =
  let k = int_of_float (sqrt (float_of_int (Array.length sequence))) in
  let sorted_queries = Array.mapi ~f:(fun i q -> (i, q)) queries in
  Array.fast_sort
    ~cmp:(fun (_, q1) (_, q2) -> compare_query k q1 q2)
    sorted_queries;

  let numbers = Array.make 1000001 0 in
  let answers = Array.make (Array.length queries) 0 in

  Array.fold_left sorted_queries ~init:(-1, -1, -1)
    ~f:(fun (s_prev, e_prev, count) (i, (s, e)) ->
      if s_prev = -1 then (
        let new_count = ref 0 in
        for j = s to e do
          let n = sequence.(j) in
          if numbers.(n) = 0 then (
            incr new_count;
            numbers.(n) <- 1)
          else numbers.(n) <- numbers.(n) + 1
        done;
        answers.(i) <- !new_count;
        (s, e, !new_count))
      else
        let new_count = ref count in
        for j = s_prev to s - 1 do
          let n = sequence.(j) in
          if numbers.(n) = 1 then (
            decr new_count;
            numbers.(n) <- 0)
          else numbers.(n) <- numbers.(n) - 1
        done;
        for j = s to s_prev - 1 do
          let n = sequence.(j) in
          if numbers.(n) = 0 then (
            incr new_count;
            numbers.(n) <- 1)
          else numbers.(n) <- numbers.(n) + 1
        done;
        for j = e_prev + 1 to e do
          let n = sequence.(j) in
          if numbers.(n) = 0 then (
            incr new_count;
            numbers.(n) <- 1)
          else numbers.(n) <- numbers.(n) + 1
        done;
        for j = e + 1 to e_prev do
          let n = sequence.(j) in
          if numbers.(n) = 1 then (
            decr new_count;
            numbers.(n) <- 0)
          else numbers.(n) <- numbers.(n) - 1
        done;
        answers.(i) <- !new_count;
        (s, e, !new_count))
  |> ignore;
  answers

let () =
  let _ = read_int () in
  let sequence =
    read_line ()
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string |> Array.of_list
  in
  let m = read_int () in
  let queries =
    Array.init m ~f:(fun _ ->
        let s, e =
          read_line ()
          |> String.split_on_char ~sep:' '
          |> List.map ~f:int_of_string
          |> fun xs -> (List.nth xs 0, List.nth xs 1)
        in
        (s - 1, e - 1))
  in
  solve sequence queries |> Array.iter ~f:(Printf.printf "%d\n")
