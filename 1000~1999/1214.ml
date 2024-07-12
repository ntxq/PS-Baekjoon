open! StdLabels
open! MoreLabels

let solve d p q =
  let rec loop idx acc =
    if idx < 0
    then acc
    else (
      let rest = d - (idx * p) in
      let m = (rest / q) + if rest mod q = 0 then 0 else 1 in
      let payment = (idx * p) + (m * q) in
      if acc = payment then acc else loop (idx - 1) (min acc payment))
  in
  let n = (d / p) + 1 in
  loop (n - 1) (n * p)
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ d; p; q ] ->
    let p' = max p q in
    let q' = min p q in
    solve d p' q' |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
