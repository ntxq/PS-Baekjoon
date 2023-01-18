open! StdLabels
open! MoreLabels

module LazySegmentTree = struct
  type t = { n : int; tree : int64 array; lazy_tree : int64 array }

  let build data =
    let n = Array.length data in
    let tree = Array.make (4 * n) 0L in
    let lazy_tree = Array.make (4 * n) 0L in

    let rec loop v tl tr =
      if tl = tr then tree.(v) <- data.(tl)
      else
        let tm = (tl + tr) / 2 in
        loop (2 * v) tl tm;
        loop ((2 * v) + 1) (tm + 1) tr;
        tree.(v) <- Int64.add tree.(2 * v) tree.((2 * v) + 1)
    in
    loop 1 0 (n - 1);
    { n; tree; lazy_tree }

  let push { tree; lazy_tree; _ } v tl tr =
    tree.(v) <-
      Int64.add tree.(v) (Int64.mul lazy_tree.(v) (Int64.of_int (tr - tl + 1)));
    if tl <> tr then (
      lazy_tree.(2 * v) <- Int64.add lazy_tree.(2 * v) lazy_tree.(v);
      lazy_tree.((2 * v) + 1) <- Int64.add lazy_tree.((2 * v) + 1) lazy_tree.(v));
    lazy_tree.(v) <- 0L

  let update ({ n; tree; lazy_tree } as segtree) l r addend =
    let rec loop v tl tr l r =
      push segtree v tl tr;
      if l > tr || r < tl then ()
      else if l <= tl && tr <= r then (
        tree.(v) <-
          Int64.add tree.(v) (Int64.mul addend (Int64.of_int (tr - tl + 1)));
        if tl <> tr then (
          lazy_tree.(2 * v) <- Int64.add lazy_tree.(2 * v) addend;
          lazy_tree.((2 * v) + 1) <- Int64.add lazy_tree.((2 * v) + 1) addend))
      else
        let tm = (tl + tr) / 2 in
        loop (2 * v) tl tm l r;
        loop ((2 * v) + 1) (tm + 1) tr l r;
        tree.(v) <- Int64.add tree.(2 * v) tree.((2 * v) + 1)
    in
    loop 1 0 (n - 1) l r;
    segtree

  let query ({ n; tree; _ } as segtree) l r =
    let rec loop v tl tr l r =
      push segtree v tl tr;
      if l > tr || r < tl then 0L
      else if l <= tl && tr <= r then tree.(v)
      else
        let tm = (tl + tr) / 2 in
        Int64.add (loop (2 * v) tl tm l r) (loop ((2 * v) + 1) (tm + 1) tr l r)
    in
    (loop 1 0 (n - 1) l r, segtree)
end

let () =
  let n, m, k =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> fun xs -> (List.nth xs 0, List.nth xs 1, List.nth xs 2)
  in
  let segtree =
    Array.init n ~f:(fun _ -> input_line stdin |> Int64.of_string)
    |> LazySegmentTree.build
  in
  List.init ~len:(m + k) ~f:Fun.id
  |> List.fold_left
       ~f:(fun segtree _ ->
         match
           input_line stdin
           |> String.split_on_char ~sep:' '
           |> List.map ~f:Int64.of_string
         with
         | 1L :: xs ->
             LazySegmentTree.update segtree
               (Int64.to_int (List.nth xs 0) - 1)
               (Int64.to_int (List.nth xs 1) - 1)
               (List.nth xs 2)
         | 2L :: xs ->
             let ans, new_tree =
               LazySegmentTree.query segtree
                 (Int64.to_int (List.nth xs 0) - 1)
                 (Int64.to_int (List.nth xs 1) - 1)
             in
             output_string stdout (Int64.to_string ans ^ "\n");
             new_tree
         | _ -> assert false)
       ~init:segtree
  |> (ignore : LazySegmentTree.t -> unit)
