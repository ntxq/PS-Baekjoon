let countResult rowList colList =
  let rowCount = (List.length rowList) - (List.fold_left (fun acc x -> if x then acc + 1 else acc) 0 rowList)
  and colCount = (List.length colList) - (List.fold_left (fun acc x -> if x then acc + 1 else acc) 0 colList) 
  in
  if rowCount > colCount then rowCount else colCount

let countSecurity rows cols =
  let rec loop rowList colList idx = function
    | [] -> countResult rowList colList
    | line :: lines -> 
      let rowPresent = List.exists (fun c -> c = 'X') line in
      let rowList' = List.mapi (fun i row -> if i = idx then rowPresent else row) rowList
      and colList' = List.map2 (fun col c -> if c = 'X' then true else col) colList line
      in
      loop rowList' colList' (idx + 1) lines
  in
  loop (List.init rows (fun _ -> false)) (List.init cols (fun _ -> false)) 0

let () =
  read_line () 
  |> String.split_on_char ' ' 
  |> List.map int_of_string 
  |> (function
    | [rows; cols] -> List.init rows (fun _ -> read_line () |> String.to_seq |> List.of_seq) |> countSecurity rows cols
    | _ -> failwith "Invalid input")
  |> string_of_int
  |> print_endline