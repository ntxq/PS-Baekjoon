let yCost xs =
  List.fold_left (fun acc x -> acc + (x / 30) * 10 + 10) 0 xs

let mCost xs =
  List.fold_left (fun acc x -> acc + (x/ 60) * 15 + 15) 0 xs

let () =
  let _ = read_int () in
  let xs = read_line () |> String.split_on_char ' ' |> List.map int_of_string in
  let ySum = yCost xs in
  let mSum = mCost xs in
  if ySum < mSum then print_endline ("Y " ^ string_of_int ySum)
  else if mSum < ySum then print_endline ("M " ^ string_of_int mSum)
  else print_endline ("Y M " ^ string_of_int ySum)