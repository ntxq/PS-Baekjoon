open! StdLabels
open! MoreLabels

let add_str set str =
  List.fold_left_map ~init:[] str ~f:(fun prev ch -> ch :: prev, ch :: prev)
  |> snd
  |> List.map ~f:List.rev
  |> List.fold_left ~init:None ~f:(fun cnt prefix ->
    match cnt, Hashtbl.mem set prefix with
    | None, true -> None
    | None, false ->
      Hashtbl.add set ~key:prefix ~data:();
      Some (List.length prefix)
    | Some cnt, true -> Some cnt
    | Some cnt, false ->
      Hashtbl.add set ~key:prefix ~data:();
      Some cnt)
  |> Option.get
;;

let () =
  let n = input_line stdin |> int_of_string in
  let set = Hashtbl.create (n * n) in
  let lines =
    List.init ~len:n ~f:(fun _ ->
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string)
    |> List.sort ~cmp:(fun a b ->
      let alen = List.length a in
      let blen = List.length b in
      if alen = blen then 0 else if alen < blen then 1 else -1)
  in
  List.fold_left lines ~init:0 ~f:(fun cnt line -> max cnt (add_str set line))
  |> Printf.sprintf "%d\n"
  |> output_string stdout
;;
