let countSupporters allStudents idx candidate =
  List.filteri (fun i _ -> i != idx) allStudents
  |> List.map (fun student -> List.exists2 (fun a b -> a = b) student candidate)
  |> List.fold_left (fun acc x -> acc + (if x then 1 else 0)) 0

let findPresident countList =
  List.mapi (fun i count -> (i, count)) countList
  |> List.sort (fun (_, a) (_, b) -> compare b a)
  |> List.hd
  |> fst
  |> ( + ) 1

let () =
  let students = List.init (read_int ()) (fun _ -> read_line () |> String.split_on_char ' ' |> List.map int_of_string) in
  List.mapi (countSupporters students) students
  |> findPresident
  |> string_of_int
  |> print_endline
