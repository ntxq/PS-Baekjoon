open! StdLabels
open! MoreLabels

module Vertices = struct
  type t = { x : int; y : int * int; is_start : bool }

  let create_vertices x1 y1 x2 y2 =
    ( { x = x1; y = (y1, y2); is_start = true },
      { x = x2; y = (y1, y2); is_start = false } )

  let compare v1 v2 = compare v1.x v2.x
  let get_range v = v.y
  let get_addend v = if v.is_start then 1 else -1
end

module SegmentTree = struct
  type t = { n : int; covers : int array; counts : int array }

  let empty n =
    { n; covers = Array.make (4 * n) 0; counts = Array.make (4 * n) 0 }

  let all_counts { counts; _ } = counts.(1)

  let update { n; covers; counts } l r addend =
    let rec loop v tl tr l r addend =
      (if l > r then ()
      else if l = tl && tr = r then covers.(v) <- covers.(v) + addend
      else
        let tm = (tl + tr) / 2 in
        loop (2 * v) tl tm l (min r tm) addend;
        loop ((2 * v) + 1) (tm + 1) tr (max (tm + 1) l) r addend);

      if covers.(v) > 0 then counts.(v) <- tr - tl + 1
      else if tl = tr then counts.(v) <- 0
      else counts.(v) <- counts.(2 * v) + counts.((2 * v) + 1)
    in
    loop 1 0 (n - 1) l r addend
end

let rec get_area idx acc segtree vertices =
  if idx = Array.length vertices then acc
  else if idx = 0 then (
    let y1, y2 = Vertices.get_range vertices.(0) in
    SegmentTree.update segtree y1 (y2 - 1) 1;
    get_area (idx + 1) acc segtree vertices)
  else
    let x_diff = vertices.(idx).x - vertices.(idx - 1).x in
    let y1, y2 = Vertices.get_range vertices.(idx) in
    let addend = Vertices.get_addend vertices.(idx) in
    let acc = acc + (x_diff * SegmentTree.all_counts segtree) in
    SegmentTree.update segtree y1 (y2 - 1) addend;
    get_area (idx + 1) acc segtree vertices

let () =
  let n = input_line stdin |> int_of_string in
  let segtree = SegmentTree.empty 30001 in

  let vertices =
    Array.init n ~f:(fun _ ->
        input_line stdin
        |> String.split_on_char ~sep:' '
        |> List.map ~f:int_of_string
        |> function
        | [ x1; y1; x2; y2 ] -> Vertices.create_vertices x1 y1 x2 y2
        | _ -> assert false)
    |> Array.fold_left ~init:[] ~f:(fun acc (v1, v2) -> v1 :: v2 :: acc)
    |> Array.of_list
  in
  Array.fast_sort ~cmp:Vertices.compare vertices;
  output_string stdout ((get_area 0 0 segtree vertices |> string_of_int) ^ "\n")
