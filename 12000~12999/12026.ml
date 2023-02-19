open! StdLabels
open! MoreLabels

let boj_index c =
  match c with 'B' -> 0 | 'O' -> 1 | 'J' -> 2 | _ -> assert false

let is_safe u v =
  let u_idx = boj_index u in
  let v_idx = boj_index v in
  (u_idx + 1) mod 3 = v_idx

let bojStreet board =
  let dp = Array.make (Array.length board) Int.max_int in
  dp.(0) <- 0;

  let rec update u v dist =
    if v = Array.length board || dp.(u) = Int.max_int then ()
    else if is_safe board.(u) board.(v) then (
      dp.(v) <- min dp.(v) (dp.(u) + (dist * dist));
      update u (v + 1) (dist + 1))
    else update u (v + 1) (dist + 1)
  in

  let rec loop u =
    if u = Array.length board then ()
    else (
      update u (u + 1) 1;
      loop (u + 1))
  in

  loop 0;

  if dp.(Array.length board - 1) = Int.max_int then -1
  else dp.(Array.length board - 1)

let () =
  let _ = input_line stdin in
  let board = input_line stdin |> String.to_seq |> Array.of_seq in
  bojStreet board |> Printf.sprintf "%d\n" |> output_string stdout
