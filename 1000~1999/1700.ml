open! StdLabels
open! MoreLabels
module IntSet = Set.Make (Int)

let find_idx x ys =
  List.mapi ys ~f:(fun i y -> (i, y))
  |> List.find_map ~f:(fun (i, y) -> if x = y then Some i else None)

let find_opt cache ys =
  IntSet.to_seq cache
  |> Seq.map (fun x -> (x, find_idx x ys))
  |> Seq.fold_left
       (fun (acc, accIdx) (x, idx) ->
         match (accIdx, idx) with
         | _, None -> (x, idx)
         | None, Some _ -> (acc, accIdx)
         | Some a, Some b -> if a < b then (x, idx) else (acc, accIdx))
       (-1, Some Int.min_int)
  |> fst

let rec count_faults n cache xs count =
  match xs with
  | [] -> count
  | y :: ys ->
      if IntSet.mem y cache then count_faults n cache ys count
      else if IntSet.cardinal cache < n then
        count_faults n (IntSet.add y cache) ys count
      else
        let out = find_opt cache ys in
        let new_cache = IntSet.remove out cache |> IntSet.add y in
        count_faults n new_cache ys (count + 1)

let () =
  let n =
    read_line ()
    |> String.split_on_char ~sep:' '
    |> (fun xs -> List.nth xs 0)
    |> int_of_string
  in
  read_line ()
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string
  |> (fun xs -> count_faults n IntSet.empty xs 0)
  |> Printf.printf "%d\n"
