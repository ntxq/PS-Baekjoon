open! Core

let find_majority votes =
  let counts = String.Table.create () in
  List.iter votes ~f:(fun name -> Hashtbl.incr counts name);
  Hashtbl.to_alist counts
  |> List.Assoc.inverse
  |> List.Assoc.sort_and_group ~compare:Int.compare
  |> List.last_exn
  |> snd
  |> function
  | [ name ] -> name
  | _ -> "Runoff!"
;;

let () =
  let result =
    In_channel.input_lines In_channel.stdin |> List.drop_last_exn |> find_majority
  in
  Out_channel.output_string stdout [%string "%{result}\n"]
;;
