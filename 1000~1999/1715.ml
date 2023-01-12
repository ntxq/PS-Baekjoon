open StdLabels
(* open MoreLabels *)

module type Comparable = sig
  type t

  val compare : t -> t -> int
end

module type Heap = sig
  type t
  type elt

  val empty : t
  val isEmpty : t -> bool
  val insert : elt -> t -> t

  (* val merge : t -> t -> t *)
  val findMin : t -> elt
  val deleteMin : t -> t
end

module LeftistHeap (Element : Comparable) : Heap with type elt := Element.t =
struct
  type t = E | T of int * Element.t * t * t

  let rank = function E -> 0 | T (r, _, _, _) -> r

  let makeT x a b =
    if rank a >= rank b then T (rank b + 1, x, a, b) else T (rank a + 1, x, b, a)

  let empty = E
  let isEmpty = function E -> true | T _ -> false

  let rec merge h1 h2 =
    match (h1, h2) with
    | E, h | h, E -> h
    | T (_, x, a1, b1), T (_, y, a2, b2) ->
        if Element.compare x y <= 0 then makeT x a1 (merge b1 h2)
        else makeT y a2 (merge h1 b2)

  let insert x h = merge (T (1, x, E, E)) h
  let findMin = function E -> failwith "Empty" | T (_, x, _, _) -> x
  let deleteMin = function E -> failwith "Empty" | T (_, _, a, b) -> merge a b
end

module IntHeap = LeftistHeap (Int)

let rec mergeAll acc q =
  let x = IntHeap.findMin q and q' = IntHeap.deleteMin q in
  if IntHeap.isEmpty q' then acc
  else
    let y = IntHeap.findMin q' and q'' = IntHeap.deleteMin q' in
    mergeAll (acc + x + y) (IntHeap.insert (x + y) q'')

let () =
  let len = read_int () in
  List.init ~len ~f:(fun _ -> read_int ())
  |> List.fold_left ~init:IntHeap.empty ~f:(fun q x -> IntHeap.insert x q)
  |> mergeAll 0 |> string_of_int |> print_endline
