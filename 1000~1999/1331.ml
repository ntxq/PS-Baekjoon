let duplicateCheck xs =
  let module StringSet = Set.Make(String) in
  (StringSet.of_list xs |> StringSet.cardinal) = 36

let getOffset u v =
  let rowOffset = abs (Char.code u.[0] - Char.code v.[0])
  and colOffset = abs (Char.code u.[1] - Char.code v.[1])
  in (rowOffset, colOffset)

let isValidOffset = function
  | (1, 2) | (2, 1) -> true
  | _ -> false

let isValidMove xs =
  List.map2 getOffset xs (List.tl xs @ [List.hd xs])
  |> List.for_all isValidOffset

let isValid xs =
  duplicateCheck xs && isValidMove xs

let () =
  List.init 36 (fun _ -> read_line ())
  |> isValid
  |> function
    | true -> print_endline "Valid"
    | false -> print_endline "Invalid"
