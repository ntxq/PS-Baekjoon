let () =
  read_line ()
  |> String.split_on_char ' '
  |> List.map int_of_string
  |> List.sort compare
  |> List.map string_of_int
  |> String.concat " "
  |> print_endline