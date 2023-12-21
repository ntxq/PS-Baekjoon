open! Core

let decreasing_suffixes n =
  let rec loop x acc =
    match x, acc with
    | [], _ -> acc
    | y :: ys, [] -> loop ys [ y ]
    | y :: ys, z :: _ -> if Char.(z < y) then loop ys (y :: acc) else acc
  in
  loop (String.to_list_rev n) [] |> String.of_list
;;

let () =
  (match In_channel.input_lines In_channel.stdin with
   | _ :: inputs ->
     List.map inputs ~f:(fun n ->
       [%string "The longest decreasing suffix of %{n} is %{decreasing_suffixes n}\n"])
     |> String.concat
   | [] -> assert false)
  |> Out_channel.output_string stdout
;;
