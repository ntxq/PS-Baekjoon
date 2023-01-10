open StdLabels
(* open MoreLabels *)

let filterHires xs =
  let rec loop = function
    | [] -> []
    | x :: y :: ys when x < y -> loop (x :: ys)
    | y :: ys -> y :: loop ys
  in
  loop xs |> List.length

let () =
  let t = Scanf.scanf "%d\n" Fun.id in
  List.init ~len:t ~f:(fun _ ->
      let n = Scanf.scanf "%d\n" Fun.id in
      let candidates = Array.make n 0 in
      for _ = 1 to n do
        Scanf.scanf "%d %d\n" (fun a b -> candidates.(a - 1) <- b)
      done;
      Array.to_list candidates |> filterHires |> string_of_int)
  |> List.iter ~f:print_endline
