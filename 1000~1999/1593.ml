(* open! Core *)
open! StdLabels

let char_to_idx c =
  if c >= 'a' then Char.code c - Char.code 'a' else Char.code c - Char.code 'A' + 26
;;

let equal_array a b = Array.for_all2 a b ~f:(fun a b -> Int.equal a b)

let () =
  let _ = input_line stdin in
  let target = input_line stdin in
  let glyphs = input_line stdin in
  let target_arr = Array.make 52 0 in
  String.iter target ~f:(fun c ->
    let idx = char_to_idx c in
    target_arr.(idx) <- target_arr.(idx) + 1);
  let glyphs_arr = Array.make 52 0 in
  let rec loop idx cnt =
    if idx = String.length glyphs
    then cnt
    else (
      if idx >= String.length target
      then (
        let prev = String.get glyphs (idx - String.length target) |> char_to_idx in
        glyphs_arr.(prev) <- glyphs_arr.(prev) - 1);
      let next = String.get glyphs idx |> char_to_idx in
      glyphs_arr.(next) <- glyphs_arr.(next) + 1;
      if equal_array target_arr glyphs_arr
      then loop (idx + 1) (cnt + 1)
      else loop (idx + 1) cnt)
  in
  let cnt = loop 0 0 in
  output_string stdout (string_of_int cnt ^ "\n")
;;
