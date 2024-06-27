open! StdLabels
open! MoreLabels

let char_to_code = function
  | 'a' -> 0
  | 'b' -> 1
  | 'k' -> 2
  | 'd' -> 3
  | 'e' -> 4
  | 'g' -> 5
  | 'h' -> 6
  | 'i' -> 7
  | 'l' -> 8
  | 'm' -> 9
  | 'n' -> 10
  | 'z' -> 11
  | 'o' -> 12
  | 'p' -> 13
  | 'r' -> 14
  | 's' -> 15
  | 't' -> 16
  | 'u' -> 17
  | 'w' -> 18
  | 'y' -> 19
  | _ -> assert false
;;

let replace_ng s =
  String.to_seq s
  |> List.of_seq
  |> List.fold_right ~init:[] ~f:(fun c acc ->
    match c, acc with
    | 'n', 'g' :: t -> 'z' :: t
    | c, _ -> c :: acc)
;;

let compare s1 s2 =
  let s1 = replace_ng s1 in
  let s2 = replace_ng s2 in
  let rec loop s1 s2 =
    match s1, s2 with
    | [], [] -> 0
    | [], _ -> -1
    | _, [] -> 1
    | x :: xs, y :: ys ->
      let cmp = char_to_code x - char_to_code y in
      if cmp = 0 then loop xs ys else cmp
  in
  loop s1 s2
;;

let () =
  let n = input_line stdin |> int_of_string in
  List.init ~len:n ~f:(fun _ -> input_line stdin)
  |> List.fast_sort ~cmp:compare
  |> String.concat ~sep:"\n"
  |> output_string stdout;
  output_char stdout '\n'
;;
