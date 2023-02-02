open! StdLabels
open! MoreLabels

module LCA = struct
  type t = {
    euler : int array;
    first : int array;
    height : int array;
    table : int array array;
  }

  let dfs ~n ~adj =
    let euler = Array.make ((2 * n) - 1) 0 in
    let first = Array.make n 0 in
    let height = Array.make n 0 in
    let table = Array.make_matrix ~dimx:21 ~dimy:((2 * n) - 1) 0 in

    let rec loop ~u ~prev ~h ~idx =
      height.(u) <- h + 1;
      first.(u) <- idx;
      euler.(idx) <- u;

      List.fold_left adj.(u) ~init:(idx + 1) ~f:(fun idx v ->
          if v <> prev then (
            let return_idx = loop ~u:v ~prev:u ~h:height.(u) ~idx in
            euler.(return_idx) <- u;
            return_idx + 1)
          else idx)
    in
    ignore (loop ~u:0 ~prev:(-1) ~h:0 ~idx:0 : int);
    { euler; first; height; table }

  let solve { euler; height; table; first } queries =
    let n = Array.length euler in
    Array.blit ~src:euler ~src_pos:0 ~dst:table.(0) ~dst_pos:0 ~len:n;

    let lg = Array.make (n + 1) 0 in
    for i = 2 to n do
      lg.(i) <- lg.(i / 2) + 1
    done;

    for j = 1 to 20 do
      for i = 0 to n - (1 lsl j) do
        table.(j).(i) <-
          (if
           height.(table.(j - 1).(i))
           < height.(table.(j - 1).(i + (1 lsl (j - 1))))
          then table.(j - 1).(i)
          else table.(j - 1).(i + (1 lsl (j - 1))))
      done
    done;

    List.iter queries ~f:(fun (u, v) ->
        let l = min first.(u) first.(v) in
        let r = max first.(u) first.(v) in

        let i = lg.(r - l + 1) in
        let lca =
          if height.(table.(i).(l)) < height.(table.(i).(r - (1 lsl i) + 1))
          then table.(i).(l) + 1
          else table.(i).(r - (1 lsl i) + 1) + 1
        in
        output_string stdout (Printf.sprintf "%d\n" lca))
end

let () =
  let n = input_line stdin |> int_of_string in
  let adj = Array.make (n + 1) [] in
  for _ = 1 to n - 1 do
    input_line stdin |> fun s ->
    Scanf.sscanf s "%d %d" (fun u v ->
        adj.(u - 1) <- (v - 1) :: adj.(u - 1);
        adj.(v - 1) <- (u - 1) :: adj.(v - 1))
  done;

  let m = input_line stdin |> int_of_string in
  let queries =
    List.init ~len:m ~f:(fun _ ->
        input_line stdin |> fun s ->
        Scanf.sscanf s "%d %d" (fun u v -> (u - 1, v - 1)))
  in

  LCA.solve (LCA.dfs ~n ~adj) queries
