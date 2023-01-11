open StdLabels
(* open MoreLabels *)

let bfs board root =
  let q = Queue.create () in
  let dist =
    Array.make_matrix ~dimx:(Array.length board)
      ~dimy:(Array.length board.(0))
      0
  in
  let maxDist = ref 0 in

  Queue.add root q;
  dist.(fst root).(snd root) <- 1;

  while not (Queue.is_empty q) do
    let x, y = Queue.take q in
    let d = dist.(x).(y) in
    if d > !maxDist then maxDist := d;

    List.iter
      [ (x - 1, y); (x + 1, y); (x, y - 1); (x, y + 1) ]
      ~f:(fun (x, y) ->
        if
          0 <= x
          && x < Array.length board
          && 0 <= y
          && y < Array.length board.(0)
          && board.(x).(y)
          && dist.(x).(y) = 0
        then (
          dist.(x).(y) <- d + 1;
          Queue.add (x, y) q))
  done;
  !maxDist - 1

let findMaxDist board =
  List.init ~len:(Array.length board) ~f:(fun x ->
      List.init
        ~len:(Array.length board.(0))
        ~f:(fun y -> if board.(x).(y) then bfs board (x, y) else 0))
  |> List.fold_left ~init:0 ~f:(fun acc xs ->
         max acc (List.fold_left ~init:0 ~f:max xs))

let () =
  let rows, _ =
    read_line () |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    |> function
    | [ rows; cols ] -> (rows, cols)
    | _ -> failwith "invalid input"
  in
  let board =
    Array.init rows ~f:(fun _ ->
        read_line () |> String.to_seq |> Array.of_seq
        |> Array.map ~f:(function 'L' -> true | _ -> false))
  in
  findMaxDist board |> string_of_int |> print_endline