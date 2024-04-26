(* open! Core *)
open! StdLabels
open! MoreLabels

let find_jump_score n points =
  let dp = Array.make n (-5000000000000L) in
  dp.(0) <- Int64.of_int points.(0);
  let rec loop idx jump =
    if idx >= n
    then ()
    else if idx - jump < 0
    then loop (idx + 1) jump
    else (
      let score = Int64.(add (of_int points.(idx)) dp.(idx - jump)) in
      dp.(idx) <- max dp.(idx) score;
      loop (idx + 1) jump)
  in
  for i = n - 1 downto 1 do
    loop 0 i
  done;
  dp.(n - 1)
;;

let () =
  let n = input_line stdin |> int_of_string in
  let points =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> Array.of_list
  in
  find_jump_score n points |> Int64.to_string |> output_string stdout;
  output_char stdout '\n'
;;
