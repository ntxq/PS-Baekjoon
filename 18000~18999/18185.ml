open! StdLabels
open! MoreLabels

let buy_ramen stocks =
  let dp = Array.init (Array.length stocks) ~f:(fun _ -> Array.make 3 0) in
  dp.(0).(0) <- stocks.(0);

  let rec loop idx =
    if idx = Array.length stocks then
      Array.fold_left dp ~init:0 ~f:(fun acc -> function
        | [| x; y; z |] -> acc + (3 * x) + (5 * y) + (7 * z) | _ -> assert false)
    else
      let double = min dp.(idx - 1).(0) stocks.(idx) in
      stocks.(idx) <- stocks.(idx) - double;
      dp.(idx - 1).(0) <- dp.(idx - 1).(0) - double;
      dp.(idx).(1) <- double;

      let triple = min dp.(idx - 1).(1) stocks.(idx) in
      stocks.(idx) <- stocks.(idx) - triple;
      dp.(idx - 1).(1) <- dp.(idx - 1).(1) - triple;
      dp.(idx).(2) <- triple;

      dp.(idx).(0) <- stocks.(idx);
      loop (idx + 1)
  in

  loop 1

let () =
  let _ = read_int () in
  let stocks =
    read_line ()
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string |> Array.of_list
  in
  buy_ramen stocks |> string_of_int |> print_endline
