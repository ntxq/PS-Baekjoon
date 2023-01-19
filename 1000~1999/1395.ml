open! StdLabels
open! MoreLabels

module LazySegmentTree = struct
  type t = { n : int; tree : int array; lazy_tree : bool array }

  let empty len =
    {
      n = len;
      tree = Array.make (len * 4) 0;
      lazy_tree = Array.make (len * 4) false;
    }

  let push { tree; lazy_tree; _ } v tl tr =
    if lazy_tree.(v) then (
      tree.(v) <- tr - tl + 1 - tree.(v);
      lazy_tree.(v) <- false;
      if tl <> tr then (
        lazy_tree.(2 * v) <- not lazy_tree.(2 * v);
        lazy_tree.((2 * v) + 1) <- not lazy_tree.((2 * v) + 1)))

  let update ({ n; tree; lazy_tree } as segtree) l r =
    let rec loop v tl tr l r =
      push segtree v tl tr;
      if l > r then ()
      else if l <= tl && tr <= r then (
        tree.(v) <- tr - tl + 1 - tree.(v);
        if tl <> tr then (
          lazy_tree.(2 * v) <- not lazy_tree.(2 * v);
          lazy_tree.((2 * v) + 1) <- not lazy_tree.((2 * v) + 1)))
      else
        let tm = (tl + tr) / 2 in
        loop (2 * v) tl tm l (min tm r);
        loop ((2 * v) + 1) (tm + 1) tr (max (tm + 1) l) r;
        tree.(v) <- tree.(2 * v) + tree.((2 * v) + 1)
    in

    loop 1 0 (n - 1) l r;
    segtree

  let query ({ n; tree; _ } as segtree) l r =
    let rec loop v tl tr l r =
      push segtree v tl tr;
      if l > r then 0
      else if l <= tl && tr <= r then tree.(v)
      else
        let tm = (tl + tr) / 2 in
        loop (2 * v) tl tm l (min tm r)
        + loop ((2 * v) + 1) (tm + 1) tr (max (tm + 1) l) r
    in
    (loop 1 0 (n - 1) l r, segtree)
end

let () =
  let n, m =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> fun xs -> (List.nth xs 0, List.nth xs 1)
  in
  let segtree = LazySegmentTree.empty n in
  List.init ~len:m ~f:Fun.id
  |> List.fold_left ~init:segtree ~f:(fun segtree _ ->
         let o, s, t =
           input_line stdin
           |> String.split_on_char ~sep:' '
           |> List.map ~f:int_of_string
           |> fun xs -> (List.nth xs 0, List.nth xs 1 - 1, List.nth xs 2 - 1)
         in
         if o = 0 then LazySegmentTree.update segtree s t
         else
           let sum, new_segtree = LazySegmentTree.query segtree s t in
           output_string stdout (string_of_int sum ^ "\n");
           new_segtree)
  |> (ignore : LazySegmentTree.t -> unit)
