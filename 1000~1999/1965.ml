open StdLabels

let countMax boxes =
  let dp = Array.make (Array.length boxes) 0 in
  for i = 0 to Array.length boxes - 1 do
    for j = 0 to i - 1 do
      if boxes.(j) < boxes.(i) then dp.(i) <- max dp.(i) (dp.(j) + 1)
    done
  done;
  Array.fold_left ~f:max ~init:0 dp + 1

let () =
  read_int () |> ignore;
  read_line ()
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string |> Array.of_list |> countMax |> string_of_int
  |> print_endline
