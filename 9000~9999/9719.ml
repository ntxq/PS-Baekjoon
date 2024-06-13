open! StdLabels
open! MoreLabels

let check_bipartite adj colors s =
  let q = Queue.create () in
  Queue.push s q;
  colors.(s) <- 0;
  let rec loop () =
    if Queue.is_empty q
    then true
    else (
      let u = Queue.pop q in
      List.for_all adj.(u) ~f:(fun v ->
        if colors.(v) = -1
        then (
          colors.(v) <- 1 - colors.(u);
          Queue.push v q;
          true)
        else colors.(v) != colors.(u))
      && loop ())
  in
  loop ()
;;

let () =
  let t = input_line stdin |> int_of_string in
  for _ = 1 to t do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ v; e ] ->
      let adj = Array.init v ~f:(fun _ -> []) in
      for _ = 0 to e do
        match
          input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
        with
        | [ u; v ] ->
          adj.(u) <- v :: adj.(u);
          adj.(v) <- u :: adj.(v)
        | [] -> ()
        | exception _ -> ()
        | _ -> assert false
      done;
      let colors = Array.make v (-1) in
      let rec loop u acc =
        if u = v
        then 2 lsl (acc - 1)
        else if colors.(u) != -1
        then loop (u + 1) acc
        else if check_bipartite adj colors u
        then loop (u + 1) (acc + 1)
        else -1
      in
      loop 0 0 |> string_of_int |> output_string stdout;
      output_char stdout '\n'
    | _ -> assert false
  done
;;
