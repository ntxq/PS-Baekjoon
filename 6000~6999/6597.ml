(* open! Core *)
open! StdLabels

let rec postorder root s t preord inord =
  if s >= t
  then ()
  else (
    let rec loop idx =
      if preord.(root) = inord.(idx)
      then (
        postorder (root + 1) s idx preord inord;
        postorder (root + 1 + (idx - s)) (idx + 1) t preord inord;
        output_char stdout preord.(root))
      else loop (idx + 1)
    in
    loop 0)
;;

let () =
  let rec loop () =
    match input_line stdin |> String.split_on_char ~sep:' ' with
    | exception End_of_file -> ()
    | [ preord; inord ] ->
      let preord = String.to_seq preord |> Array.of_seq in
      let inord = String.to_seq inord |> Array.of_seq in
      postorder 0 0 (Array.length preord) preord inord;
      output_char stdout '\n';
      loop ()
    | _ -> assert false
  in
  loop ()
;;
