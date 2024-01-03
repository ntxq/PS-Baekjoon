open! Core

let is_vowel = function
  | 'a' | 'e' | 'i' | 'o' | 'u' -> true
  | _ -> false
;;

let is_punctuation = Char.is_alpha |> Fn.non

let remove_vowels word =
  let rec loop chars count acc =
    match chars, count with
    | [], _ -> List.rev acc
    | xs, 0 -> List.rev_append acc xs
    | x :: xs, cnt -> if is_vowel x then loop xs (cnt - 1) acc else loop xs cnt (x :: acc)
  in
  let chars = String.to_list word in
  let count = List.count chars ~f:is_vowel in
  loop chars (count / 2) [] |> String.of_char_list
;;

let remove_consecutive_spaces text =
  let rec loop chars acc =
    match chars, acc with
    | [], _ -> List.rev acc
    | x :: xs, [] -> loop xs [ x ]
    | x :: xs, y :: _ ->
      if Char.equal x ' ' && Char.equal y ' ' then loop xs acc else loop xs (x :: acc)
  in
  loop (String.to_list text) [] |> String.of_char_list
;;

let translate input =
  let translated =
    let%map.List line = List.map input ~f:(String.split ~on:' ') in
    List.map line ~f:String.lowercase
    |> List.map ~f:(function
      | "of" | "to" | "into" | "onto" | "above" | "below" | "from" | "by" | "is" | "at" ->
        "of"
      | word -> word)
    |> List.map ~f:remove_vowels
    |> List.map ~f:(fun word ->
      String.to_list word |> List.filter ~f:(Fn.non is_punctuation) |> String.of_char_list)
    |> String.concat ~sep:" "
  in
  String.concat translated ~sep:" "
  |> remove_consecutive_spaces
  |> String.strip
  |> String.split ~on:' '
;;

let () =
  let output = In_channel.input_lines In_channel.stdin |> List.tl_exn |> translate in
  let rec loop lines count =
    match lines with
    | [] -> ()
    | x :: xs ->
      Out_channel.output_string stdout x;
      let next_count = count + String.length x in
      if next_count > 20
      then (
        Out_channel.output_char stdout '\n';
        loop xs 0)
      else (
        Out_channel.output_char stdout ' ';
        loop xs next_count)
  in
  loop output 0
;;
