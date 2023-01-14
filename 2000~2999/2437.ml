open! StdLabels
open! MoreLabels

let findMissing ws =
  List.fold_left ws ~init:(0, None) ~f:(fun (prev, ans) x ->
      match ans with
      | Some _ -> (x, ans)
      | None ->
          if prev >= x || prev + 1 = x then (prev + x, ans)
          else (prev, Some (prev + 1)))
  |> function
  | _, Some x -> x
  | sum, None -> sum + 1

let () =
  let _ = read_int () in
  read_line ()
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string
  |> List.fast_sort ~cmp:Int.compare
  |> findMissing |> string_of_int |> print_endline
