(* open! StdLabels
   open! MoreLabels *)

module type Ordered = sig
  type t

  val compare : t -> t -> int
end

exception Empty

module Make (X : Ordered) = struct
  (* The heap is encoded in the array [data], where elements are stored
     from [0] to [size - 1]. From an element stored at [i], the left
     (resp. right) subtree, if any, is rooted at [2*i+1] (resp. [2*i+2]). *)

  type t = {
    mutable size : int;
    mutable data : X.t array;
    dummy : X.t;
    min_cap : int; (* minimal capacity, as given initially *)
  }
  (* invariant 0 <= size <= length data *)
  (* invariant data[size..] only contains dummy *)

  let create ~dummy n =
    if n < 0 || n > Sys.max_array_length then invalid_arg "create";
    let n = max 16 n in
    { size = 0; data = Array.make n dummy; dummy; min_cap = n }

  let length h = h.size
  let is_empty h = h.size = 0

  (* [enlarge] doubles the size of [data] *)
  let enlarge h =
    let n = h.size in
    assert (n > 0 && n = Array.length h.data);
    let n' = min (2 * n) Sys.max_array_length in
    if n' = n then failwith "maximum capacity reached";
    let d = h.data in
    let d' = Array.make n' h.dummy in
    Array.blit d 0 d' 0 n;
    h.data <- d'

  let shrink h =
    let n = Array.length h.data in
    let n' = max h.min_cap (n / 2) in
    assert (h.size <= n' && n' <= n);
    if n' < n then (
      let d = h.data in
      let d' = Array.make n' h.dummy in
      Array.blit d 0 d' 0 h.size;
      h.data <- d')

  let add h x =
    let n = h.size in
    if n == Array.length h.data then enlarge h;
    let d = h.data in
    let rec moveup i =
      let fi = (i - 1) / 2 in
      if i > 0 && X.compare d.(fi) x > 0 then (
        d.(i) <- d.(fi);
        moveup fi)
      else d.(i) <- x
    in
    moveup n;
    h.size <- n + 1

  let minimum h =
    if h.size <= 0 then raise Empty;
    h.data.(0)

  let rec movedown d n i x =
    let j = (2 * i) + 1 in
    if j < n then
      let j =
        let j' = j + 1 in
        if j' < n && X.compare d.(j') d.(j) < 0 then j' else j
      in
      if X.compare d.(j) x < 0 then (
        d.(i) <- d.(j);
        movedown d n j x)
      else d.(i) <- x
    else d.(i) <- x

  let remove h =
    if h.size <= 0 then raise Empty;
    let n = h.size - 1 in
    h.size <- n;
    let d = h.data in
    let x = d.(n) in
    d.(n) <- h.dummy;
    movedown d n 0 x;
    if 4 * h.size < Array.length h.data then shrink h

  let remove_and_add h x =
    if h.size = 0 then add h x else movedown h.data h.size 0 x

  let pop_minimum h =
    let m = minimum h in
    remove h;
    m

  let iter f h =
    let d = h.data in
    for i = 0 to h.size - 1 do
      f d.(i)
    done

  let fold f h x0 =
    let n = h.size in
    let d = h.data in
    let rec foldrec x i = if i >= n then x else foldrec (f d.(i) x) (succ i) in
    foldrec x0 0
end

module MaxHeap = Make (struct
  type t = int

  let compare x y = Int.compare y x
end)

module PairHeap = Make (struct
  type t = int * int

  let compare (a, b) (c, d) =
    let c = Int.compare a c in
    if c <> 0 then c else Int.compare b d
end)

let kth_dijkstra adj n k =
  let dist = Array.init n (fun _ -> MaxHeap.create ~dummy:Int.max_int k) in
  let pq = PairHeap.create ~dummy:(Int.max_int, -1) n in

  MaxHeap.add dist.(0) 0;
  PairHeap.add pq (0, 0);

  while not (PairHeap.is_empty pq) do
    let d, u = PairHeap.pop_minimum pq in

    List.iter
      (fun (v, w) ->
        let d' = d + w in
        if MaxHeap.length dist.(v) < k then (
          MaxHeap.add dist.(v) d';
          PairHeap.add pq (d', v))
        else if d' < MaxHeap.minimum dist.(v) then (
          MaxHeap.remove_and_add dist.(v) d';
          PairHeap.add pq (d', v)))
      adj.(u)
  done;

  dist

let () =
  let n, m, k =
    read_line () |> String.split_on_char ' ' |> List.map int_of_string
    |> fun xs -> (List.nth xs 0, List.nth xs 1, List.nth xs 2)
  in
  let adj = Array.init n (fun _ -> ref []) in
  for _ = 1 to m do
    let u, v, w =
      read_line () |> String.split_on_char ' ' |> List.map int_of_string
      |> fun xs -> (List.nth xs 0, List.nth xs 1, List.nth xs 2)
    in
    adj.(u - 1) := (v - 1, w) :: !(adj.(u - 1))
  done;

  kth_dijkstra (Array.map ( ! ) adj) n k
  |> Array.iter (fun h ->
         if MaxHeap.length h < k then print_endline "-1"
         else print_endline (string_of_int (MaxHeap.minimum h)))
