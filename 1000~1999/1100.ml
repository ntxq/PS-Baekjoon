let count row line =
  let lineSeq = String.to_seqi line in
  Seq.fold_left 
    (fun acc (idx, c) -> if (idx + row) mod 2 = 0 && c = 'F' then acc + 1 else acc)
    0
    lineSeq

let solve () =
  List.init 8 (fun _ -> read_line ())
  |> List.mapi count
  |> List.fold_left ( + ) 0

let () = 
  print_int (solve ())