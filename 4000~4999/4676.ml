open! Core

let is_vowel ch =
  match ch with
  | 'a' | 'e' | 'i' | 'o' | 'u' | 'y' -> true
  | _ -> false
;;

let get_syllable word =
  let rec loop word acc =
    match word with
    | [] -> acc
    | ch :: rest ->
      if is_vowel ch
      then loop (List.drop_while rest ~f:is_vowel) (acc + 1)
      else loop rest acc
  in
  loop (String.to_list word) 0
;;

let check_haiku haiku =
  match List.map haiku ~f:get_syllable with
  | [ 5; 7; 5 ] -> "Y"
  | [ 5; 7; _ ] -> "3"
  | [ 5; _; _ ] -> "2"
  | [ _; _; _ ] -> "1"
  | _ -> "X"
;;

let () =
  let result =
    In_channel.input_lines In_channel.stdin
    |> List.drop_last_exn
    |> List.map ~f:(String.split ~on:'/')
    |> List.map ~f:check_haiku
    |> String.concat_lines
  in
  Out_channel.output_string stdout result
;;
