open! StdLabels
open! MoreLabels

let count_single names =
  let module S = Set.Make (String) in
  List.fold_left ~init:(0, S.empty)
    ~f:(fun (count, set) name ->
      if S.mem name set then (count, set) else (count + 1, S.add name set))
    names
  |> fst

let read_input len =
  let rec loop acc = function
    | 0 -> acc
    | n -> loop (input_line stdin :: acc) (n - 1)
  in
  loop [] len

let parse_input lines =
  List.fold_left ~init:([], [])
    ~f:(fun (names, groups) line ->
      if String.equal line "ENTER" then ([], names :: groups)
      else (line :: names, groups))
    lines
  |> fun (names, groups) -> names :: groups

let () =
  let len = input_line stdin |> int_of_string in
  let lines = read_input len in
  let groups = parse_input lines in
  List.fold_left ~init:0 ~f:(fun acc names -> acc + count_single names) groups
  |> string_of_int
  |> fun s -> output_string stdout (s ^ "\n")
