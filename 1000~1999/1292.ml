open! StdLabels
open! MoreLabels

let rec num_sequence acc idx =
  if idx < 50 then
    let rec loop acc n = if n = 0 then acc else loop (idx :: acc) (n - 1) in
    num_sequence (List.append acc (loop [] idx)) (idx + 1)
  else acc

let () =
  Scanf.scanf "%d %d" (fun a b ->
      num_sequence [] 1
      |> List.mapi ~f:(fun i x -> (i + 1, x))
      |> List.fold_left
           ~f:(fun acc (i, x) -> if a <= i && i <= b then acc + x else acc)
           ~init:0
      |> Printf.printf "%d\n")
