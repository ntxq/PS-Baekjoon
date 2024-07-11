open! StdLabels
open! MoreLabels

let parents = Array.init 100001 ~f:Fun.id
let sizes = Array.make 100001 1
let weight_diffs = Array.make 100001 0

let rec find_set u =
  if u = parents.(u)
  then u
  else (
    let v = find_set parents.(u) in
    weight_diffs.(u) <- weight_diffs.(u) + weight_diffs.(parents.(u));
    parents.(u) <- v;
    v)
;;

let union_sets u v weight_diff =
  let s = find_set u in
  let t = find_set v in
  if s <> t
  then
    if sizes.(s) < sizes.(t)
    then (
      parents.(s) <- t;
      sizes.(t) <- sizes.(s) + sizes.(t);
      weight_diffs.(s) <- weight_diff - weight_diffs.(u) + weight_diffs.(v))
    else (
      parents.(t) <- s;
      sizes.(s) <- sizes.(s) + sizes.(t);
      weight_diffs.(t) <- -weight_diff + weight_diffs.(u) - weight_diffs.(v))
;;

let query a b =
  let u = find_set a in
  let v = find_set b in
  if u = v then weight_diffs.(a) - weight_diffs.(b) |> string_of_int else "UNKNOWN"
;;

let () =
  let rec loop () =
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ 0; 0 ] -> ()
    | [ n; m ] ->
      for _ = 1 to m do
        match input_line stdin |> String.split_on_char ~sep:' ' with
        | [ "!"; a; b; w ] ->
          union_sets (int_of_string a) (int_of_string b) (int_of_string w)
        | [ "?"; a; b ] ->
          query (int_of_string a) (int_of_string b) |> output_string stdout;
          output_char stdout '\n'
        | _ -> assert false
      done;
      Array.iteri parents ~f:(fun i _ -> parents.(i) <- i);
      Array.fill sizes ~pos:1 ~len:n 1;
      Array.fill weight_diffs ~pos:1 ~len:n 0;
      loop ()
    | _ -> assert false
  in
  loop ()
;;
