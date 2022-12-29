let () =
  let possible = read_line () in
  let required = read_line () in
  let should_go = String.length possible >= String.length required in
  if should_go then
    print_endline "go"
  else
    print_endline "no"