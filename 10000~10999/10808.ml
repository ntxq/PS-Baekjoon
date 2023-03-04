open! StdLabels
open! MoreLabels

let () =
  let s = input_line stdin |> String.to_seq in
  let rec loop s dp =
    match s with
    | Seq.Nil -> dp
    | Seq.Cons (c, s) ->
        dp.(Char.code c - Char.code 'a') <- dp.(Char.code c - Char.code 'a') + 1;
        loop (s ()) dp
  in
  let dp = loop (s ()) (Array.make 26 0) in
  Array.iter dp ~f:(Printf.printf "%d ")
