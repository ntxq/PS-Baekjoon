open! StdLabels
open! MoreLabels

let init_basket n =
  let rec loop i acc =
    if i = 0 then acc else loop (i - 1) (Seq.cons (i, 0) acc)
  in
  loop n Seq.empty

let insert u v x baskets =
  let ( let+ ) x f = Seq.map f x in

  let+ i, y = baskets in
  if u <= i && i <= v then (i, x) else (i, y)

let rec insert_all actions baskets =
  match actions with
  | [] -> baskets
  | (u, v, x) :: actions -> insert_all actions (insert u v x baskets)

let () =
  let n, m =
    input_line stdin |> fun s -> Scanf.sscanf s "%d %d" (fun n m -> (n, m))
  in

  let baskets = init_basket n in
  let actions =
    List.init ~len:m ~f:(fun _ ->
        input_line stdin |> fun s ->
        Scanf.sscanf s "%d %d %d" (fun u v x -> (u, v, x)))
  in

  let result = insert_all actions baskets in
  Seq.iter (fun (_, x) -> output_string stdout (string_of_int x ^ " ")) result
