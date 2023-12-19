open! Core

let () =
  In_channel.input_line_exn In_channel.stdin
  |> String.split ~on:'/'
  |> List.map ~f:Int.of_string
  |> (function
        | [ k; d; a ] -> if k + a < d || d = 0 then "hasu\n" else "gosu\n"
        | _ -> assert false)
  |> Out_channel.output_string Out_channel.stdout
;;
