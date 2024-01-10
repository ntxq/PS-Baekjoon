open! Core
(* open! StdLabels *)

let count_average k numbers =
  let open Int64 in
  let prefixes = Int64.Table.create () in
  Hashtbl.add_exn prefixes ~key:0L ~data:1L;
  let rec loop count sum = function
    | [] -> count
    | x :: xs ->
      let sum = sum + x - k in
      let prev_count = Hashtbl.find_or_add prefixes sum ~default:(fun () -> 0L) in
      Hashtbl.update prefixes sum ~f:(fun _ -> prev_count + 1L);
      let count = count + prev_count in
      loop count sum xs
  in
  loop 0L 0L numbers
;;

let () =
  match
    In_channel.input_line_exn In_channel.stdin
    |> String.split ~on:' '
    |> List.map ~f:Int.of_string
  with
  | [ _; k ] ->
    let count =
      In_channel.input_line_exn In_channel.stdin
      |> String.split ~on:' '
      |> List.map ~f:Int64.of_string
      |> count_average (Int64.of_int k)
    in
    Out_channel.output_string Out_channel.stdout [%string "%{count#Int64}\n"]
  | _ -> ()
;;
