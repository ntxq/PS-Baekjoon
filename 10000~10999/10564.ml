open! StdLabels
open! MoreLabels

let push_up_count n scores =
  let dp = Array.make_matrix ~dimx:(n + 1) ~dimy:500 false in
  dp.(0).(0) <- true;

  let rec loop i j =
    if i = n then ()
    else if j = 500 then loop (i + 1) 0
    else if not dp.(i).(j) then loop i (j + 1)
    else (
      List.iter scores ~f:(fun s ->
          let next = i + j + s in
          if next <= n then dp.(next).(j + s) <- true);
      loop i (j + 1))
  in
  loop 0 0;

  let rec last_index i acc =
    if i = 500 then acc
    else if dp.(n).(i) then last_index (i + 1) i
    else last_index (i + 1) acc
  in
  last_index 0 (-1)

let () =
  let t = input_line stdin |> int_of_string in
  List.init ~len:t ~f:(fun _ ->
      let n =
        input_line stdin |> fun s -> Scanf.sscanf s "%d %d" (fun n _ -> n)
      in
      let scores =
        input_line stdin
        |> String.split_on_char ~sep:' '
        |> List.map ~f:int_of_string
      in
      push_up_count n scores)
  |> List.iter ~f:(fun x -> output_string stdout (string_of_int x ^ "\n"))
