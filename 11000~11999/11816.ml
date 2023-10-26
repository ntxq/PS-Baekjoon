open! StdLabels
open! MoreLabels

let () =
  let num = input_line stdin in
  (if String.length num > 1 && String.get num 0 = '0' && String.get num 1 != 'x'
   then String.concat ~sep:"" [ "0o"; String.sub num ~pos:1 ~len:(String.length num - 1) ]
   else num)
  |> int_of_string
  |> Printf.sprintf "%d\n"
  |> output_string stdout
;;
