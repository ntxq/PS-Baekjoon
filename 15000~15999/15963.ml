open! Core

let () =
  In_channel.input_line_exn In_channel.stdin
  |> String.split ~on:' '
  |> List.all_equal ~equal:String.equal
  |> (function
        | Some _ -> "1"
        | None -> "0")
  |> print_endline
;;
