open StdLabels
(* open MoreLabels *)

module DisjointSet : sig
  type 'a t

  val make : 'a -> 'a t

  (* val find : 'a t -> 'a t *)
  val union : 'a t -> 'a t -> 'a t
  val eq : 'a t -> 'a t -> bool
end = struct
  type 'a t = 'a content ref

  and 'a content =
    | Link of { mutable parent : 'a t }
    | Root of { mutable rank : int; value : 'a }

  let make x = ref (Root { rank = 0; value = x })

  let rec find x =
    match !x with
    | Root _ -> x
    | Link ({ parent = y } as link) ->
        let z = find y in
        if z != y then link.parent <- z;
        z

  let union x y =
    let x = find x and y = find y in
    if x == y then x
    else
      match (!x, !y) with
      | Root ({ rank = rx; _ } as rootx), Root { rank = ry; _ } ->
          if rx < ry then (
            x := Link { parent = y };
            y)
          else if rx > ry then (
            y := Link { parent = x };
            x)
          else (
            y := Link { parent = x };
            rootx.rank <- rx + 1;
            x)
      | Root _, Link _ | Link _, Root _ | Link _, Link _ -> assert false

  let eq x y = x == y || find x == find y
end

type edge = { weight : int; source : int; target : int }

let findMST (edges : edge list) (nodes : int DisjointSet.t array) =
  let edges = List.sort ~cmp:(fun a b -> compare a.weight b.weight) edges in
  List.fold_left edges ~init:0 ~f:(fun cost edge ->
      if DisjointSet.eq nodes.(edge.source) nodes.(edge.target) then cost
      else (
        ignore
          (DisjointSet.union nodes.(edge.source) nodes.(edge.target)
            : int DisjointSet.t);
        cost + edge.weight))

let () =
  let nodes = Scanf.scanf "%d\n" (fun n -> Array.init n ~f:DisjointSet.make) in
  let edges =
    Scanf.scanf "%d\n" (fun m ->
        List.init ~len:m ~f:(fun _ ->
            Scanf.scanf "%d %d %d\n" (fun s t w ->
                { weight = w; source = s - 1; target = t - 1 })))
  in
  findMST edges nodes |> Printf.printf "%d\n"
