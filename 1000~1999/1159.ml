module CharMap = Map.Make(Char)

let selection list =
  List.map (fun name -> String.get name 0) list
  |> List.fold_left (fun assoc c -> 
      CharMap.update c (function
        | None -> Some 1
        | Some n -> Some (n + 1))
        assoc)
    CharMap.empty
  |> CharMap.filter (fun _ n -> n > 4)
  |> CharMap.bindings
  |> List.map fst
  |> List.sort compare
  |> List.map (String.make 1)
  |> String.concat ""
  |> function
    | "" -> "PREDAJA"
    | s -> s

let parse () =
  let length = read_int () in
  List.init length (fun _ -> read_line ())

let () =
  parse ()
  |> selection
  |> print_endline