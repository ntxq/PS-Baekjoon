let panelWidth number =
  Seq.fold_left (fun acc -> function
    | '1' -> acc + 3
    | '0' -> acc + 5
    | _ -> acc + 4)
    1
    number

let rec solve () =
  let number = read_line () in
  if number <> "0" then 
    let () = print_endline (string_of_int (panelWidth (String.to_seq number))) in
    solve ()

let () =
  solve ()