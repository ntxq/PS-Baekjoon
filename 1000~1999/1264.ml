let countVowels s =
  String.uppercase_ascii s
  |> String.to_seq
  |> Seq.fold_left 
    (fun acc -> function
      | 'A' | 'E' | 'I' | 'O' | 'U' -> acc + 1
      | _ -> acc
    ) 0

let rec solve () =
  let s = read_line () in
  if s = "#" then
    ()
  else
    countVowels s 
    |> string_of_int
    |> print_endline
    |> solve

let () =
  solve ()
