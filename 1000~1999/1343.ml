let splitBoard s =
  String.split_on_char '.' s
  |> List.map String.length

let isValidBoard xs =
  List.for_all (fun x -> x mod 2 = 0) xs

let fillPartition len =
  let b = Buffer.create len in
  for _ = 1 to len / 4 do Buffer.add_string b "AAAA" done;
  if len mod 4 = 2 then Buffer.add_string b "BB";
  Buffer.contents b

let fillBoard xs =
  List.map fillPartition xs
  |> String.concat "."

let () =
  read_line ()
  |> splitBoard
  |> (fun xs -> if isValidBoard xs then fillBoard xs else "-1")
  |> print_endline
