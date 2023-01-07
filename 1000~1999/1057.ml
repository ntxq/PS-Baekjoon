let () =
  let a, b = Scanf.scanf "%d %d %d" (fun _ a b -> (a, b)) in
  let rec loop a b i =
    if a = b then i else loop (a - (a / 2)) (b - (b / 2)) (i + 1)
  in
  loop a b 0 |> string_of_int |> print_endline
