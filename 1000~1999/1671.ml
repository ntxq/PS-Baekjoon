open! StdLabels
open! MoreLabels

module SharkKuhn = struct
  type t = { n : int; matches : int array; adj : int array array }

  let create sharks =
    let eatable i j (a1, b1, c1) (a2, b2, c2) =
      if a1 = a2 && b1 = b2 && c1 = c2 then i < j
      else a1 <= a2 && b1 <= b2 && c1 <= c2
    in

    let n = Array.length sharks in
    let matches = Array.make n (-1) in

    let adj =
      Array.init n ~f:(fun i ->
          List.init ~len:n ~f:Fun.id
          |> List.filter ~f:(fun j -> eatable j i sharks.(j) sharks.(i))
          |> Array.of_list)
    in

    { n; matches; adj }

  let rec try_kuhn u used ({ matches; adj; _ } as state) =
    if used.(u) then false
    else (
      used.(u) <- true;
      Array.exists adj.(u) ~f:(fun v ->
          if matches.(v) = -1 || try_kuhn matches.(v) used state then (
            matches.(v) <- u;
            true)
          else false))

  let count ({ n; matches; _ } as state) =
    let used = Array.make n false in
    ignore
      (List.init ~len:n ~f:(fun i ->
           Array.fill used ~pos:0 ~len:n false;
           ignore (try_kuhn i used state);
           Array.fill used ~pos:0 ~len:n false;
           ignore (try_kuhn i used state)));
    Array.fold_left matches ~init:0 ~f:(fun acc x ->
        if x = -1 then acc + 1 else acc)
end

let () =
  let n = input_line stdin |> int_of_string in
  let sharks =
    Array.init n ~f:(fun _ ->
        input_line stdin
        |> String.split_on_char ~sep:' '
        |> List.map ~f:int_of_string
        |> fun xs -> (List.nth xs 0, List.nth xs 1, List.nth xs 2))
  in
  let state = SharkKuhn.create sharks in
  let count = SharkKuhn.count state in
  output_string stdout (string_of_int count ^ "\n")
