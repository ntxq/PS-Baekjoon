let position = function
  | true, _, _ -> 1
  | _, true, _ -> 2
  | _, _, true -> 3
  | _ -> 0

let rec swap count (a, b, c) =
  if count = 0 then print_endline (string_of_int (position (a, b, c)))
  else 
    let x, y = Scanf.scanf "%d %d\n" (fun x y -> x, y) in
    match x, y with
      | 1, 2 -> swap (count - 1) (b, a, c)
      | 1, 3 -> swap (count - 1) (c, b, a)
      | 2, 1 -> swap (count - 1) (b, a, c)
      | 2, 3 -> swap (count - 1) (a, c, b)
      | 3, 1 -> swap (count - 1) (c, b, a)
      | 3, 2 -> swap (count - 1) (a, c, b)
      | _ -> ()

let () =
  let count = Scanf.scanf "%d\n" (fun x -> x) in
  swap count (true, false, false)