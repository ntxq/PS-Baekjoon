open! StdLabels
open! MoreLabels

module Edge = struct
  type t = { s : int; t : int; w : int }

  let compare { w = w1; _ } { w = w2; _ } = Int.compare w1 w2
end

module UnionFind = struct
  type t = { parent : int array; size : int array }

  let make_set n =
    let parent = Array.init n ~f:Fun.id in
    let size = Array.make n 1 in
    { parent; size }

  let rec find_set v ({ parent; _ } as t) =
    if parent.(v) = v then v
    else
      let parent_v = find_set parent.(v) t in
      parent.(v) <- parent_v;
      parent_v

  let size v ({ size; _ } as t) = size.(find_set v t)

  let union_sets a b { parent; size } =
    let a = find_set a { parent; size } in
    let b = find_set b { parent; size } in
    if a = b then ()
    else if size.(a) < size.(b) then (
      parent.(a) <- b;
      size.(b) <- size.(b) + size.(a))
    else (
      parent.(b) <- a;
      size.(a) <- size.(a) + size.(b))
end

let () =
  let queries = Array.make 100001 (0, 0) in
  let lows = Array.make 100001 0 in
  let highs = Array.make 100001 0 in
  let results = Array.make 100001 (0, 0) in
  let groups = Array.make 100001 [] in

  let m = input_line stdin |> fun s -> Scanf.sscanf s "%d %d" (fun _ m -> m) in
  let edges =
    Array.init (m + 1) ~f:(fun i ->
        if i = 0 then Edge.{ s = 0; t = 0; w = 0 }
        else
          input_line stdin |> fun s ->
          Scanf.sscanf s "%d %d %d" (fun s t w -> Edge.{ s; t; w }))
  in
  Array.fast_sort edges ~cmp:Edge.compare;

  let q = input_line stdin |> int_of_string in
  for i = 1 to q do
    input_line stdin |> fun s ->
    Scanf.sscanf s "%d %d" (fun x y -> queries.(i) <- (x, y))
  done;

  Array.fill ~pos:1 ~len:q lows 1;
  Array.fill ~pos:1 ~len:q highs (m + 1);

  let rec loop () =
    Array.fill ~pos:0 ~len:100001 groups [];
    let flag = ref false in
    for i = 1 to q do
      if lows.(i) <> highs.(i) then (
        flag := true;
        let mid = (lows.(i) + highs.(i)) / 2 in
        groups.(mid) <- i :: groups.(mid))
    done;

    if !flag then (
      let uf = UnionFind.make_set 100001 in
      for i = 1 to m do
        let Edge.{ s; t; w } = edges.(i) in
        UnionFind.union_sets s t uf;
        List.iter groups.(i) ~f:(fun j ->
            let x, y = queries.(j) in
            let px = UnionFind.find_set x uf in
            let py = UnionFind.find_set y uf in

            if px = py then (
              highs.(j) <- i;
              results.(j) <- (w, UnionFind.size x uf))
            else lows.(j) <- i + 1)
      done;
      loop ())
  in
  loop ();

  for i = 1 to q do
    if lows.(i) = m + 1 then output_string stdout "-1\n"
    else
      output_string stdout
        (Printf.sprintf "%d %d\n" (fst results.(i)) (snd results.(i)))
  done
