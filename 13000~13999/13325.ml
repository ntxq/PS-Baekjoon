open! StdLabels
open! MoreLabels

let balance_edges edges =
  let total_edges = Array.length edges in
  let rec loop idx =
    if idx * 2 >= total_edges
    then 0L, 0L
    else (
      let lWeight, lAcc = loop (idx * 2) in
      let rWeight, rAcc = loop ((idx * 2) + 1) in
      let lEdge = edges.((idx * 2) - 1) |> Int64.of_int in
      let rEdge = edges.(idx * 2) |> Int64.of_int in
      let lTotal = Int64.add lEdge lWeight in
      let rTotal = Int64.add rEdge rWeight in
      let diff = Int64.abs (Int64.sub lTotal rTotal) in
      let weight = max lTotal rTotal in
      let acc =
        Int64.add lAcc rAcc |> Int64.add lEdge |> Int64.add rEdge |> Int64.add diff
      in
      weight, acc)
  in
  loop 1 |> snd
;;

let () =
  let _ = input_line stdin in
  let edges =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> List.cons 0
    |> Array.of_list
  in
  balance_edges edges |> Int64.to_string |> output_string stdout;
  output_char stdout '\n'
;;
