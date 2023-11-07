open! StdLabels
open! MoreLabels

let () =
  let rec loop idx =
    match input_line stdin with
    | "0" -> ()
    | _ ->
      Printf.sprintf "Case %d: Sorting... done!\n" idx |> output_string stdout;
      loop (idx + 1)
  in
  loop 1
;;
