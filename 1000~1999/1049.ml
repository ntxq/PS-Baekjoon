let min a b c = if a < b then if a < c then a else c else if b < c then b else c

let () =
  Scanf.scanf "%d %d\n" (fun n m ->
      List.init m (fun _ -> Scanf.scanf "%d %d\n" (fun a b -> (a, b)))
      |> List.fold_left
           (fun (a, b) (c, d) ->
             ((if a < c then a else c), if b < d then b else d))
           (Int.max_int, Int.max_int)
      |> fun (a, b) ->
      let allPackage = if n mod 6 = 0 then a * n / 6 else a * ((n / 6) + 1)
      and onePackage = (a * (n / 6)) + (b * (n mod 6))
      and allSingle = b * n in
      min allPackage onePackage allSingle |> string_of_int |> print_endline)
