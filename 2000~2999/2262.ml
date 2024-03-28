open! Core
(* open! StdLabels
   open! MoreLabels *)

let min_rank_sum ranks =
  let rec loop xs ranks acc =
    match xs with
    | [ _ ] -> acc
    | xs ->
      let max_rank = Set.max_elt_exn ranks in
      let max_idx =
        List.findi xs ~f:(fun _ x -> x = max_rank) |> Option.value_exn |> fst
      in
      if max_idx = 0
      then (
        let xss = List.tl_exn xs in
        loop xss (Set.remove ranks max_rank) (acc + max_rank - List.hd_exn xss))
      else if max_idx = List.length xs - 1
      then (
        let xss = List.take xs (List.length xs - 1) in
        loop xss (Set.remove ranks max_rank) (acc + max_rank - List.last_exn xss))
      else (
        let min_diff =
          max (List.nth_exn xs (max_idx - 1)) (List.nth_exn xs (max_idx + 1))
        in
        let xss = List.take xs max_idx @ List.drop xs (max_idx + 1) in
        loop xss (Set.remove ranks max_rank) (acc + max_rank - min_diff))
  in
  loop ranks (Int.Set.of_list ranks) 0
;;

let () =
  let _ = In_channel.input_line_exn In_channel.stdin in
  let ranks =
    In_channel.input_line_exn In_channel.stdin
    |> String.split ~on:' '
    |> List.map ~f:int_of_string
  in
  Out_channel.output_string Out_channel.stdout [%string "%{min_rank_sum ranks#Int}\n"]
;;
