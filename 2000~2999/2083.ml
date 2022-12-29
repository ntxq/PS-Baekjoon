let classify age weight =
  if age > 17 || weight >= 80 then "Senior"
  else "Junior"

let rec solve () =
  read_line ()
  |> String.split_on_char ' '
  |> function
    | "#" :: _ -> ()
    | name :: age :: weight :: [] ->
      let () = print_endline (name ^ " " ^ classify (int_of_string age) (int_of_string weight)) in
      solve ()
    | _ -> failwith "invalid input"

let () =
    solve ()