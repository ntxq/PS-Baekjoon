open! StdLabels
open! MoreLabels

let count num =
  let counts = Array.make 10 0 in
  let f ch =
    let idx = Char.code ch - Char.code '0' in
    counts.(idx) <- counts.(idx) + 1
  in
  Bytes.iter num ~f;
  counts.(6) <- counts.(6) + counts.(9);
  counts.(9) <- 0;
  let f idx cnt = if idx = 6 then (cnt / 2) + (cnt mod 2) else cnt in
  Array.mapi counts ~f |> Array.fold_left ~init:0 ~f:(fun acc x -> max acc x)
;;

let () =
  read_line () |> Bytes.of_string |> count |> Printf.printf "%d\n"