open! Core

let fibo_table =
  let rec loop x y acc =
    let open Int64 in
    let next = x + y in
    if next > 10000000000000000L then acc else loop y next (next :: acc)
  in
  loop 1L 1L [ 1L; 1L ] |> List.rev
;;

let single_fibo = Int64.Set.of_list fibo_table

let double_fibo =
  let nums =
    let open Int64 in
    let%bind.List x = fibo_table in
    let%map.List y = fibo_table in
    x + y
  in
  Int64.Set.of_list nums
;;

let triple_fibo =
  let nums =
    let open Int64 in
    let%bind.List x = fibo_table in
    let%bind.List y = fibo_table in
    let%map.List z = fibo_table in
    x + y + z
  in
  Int64.Set.of_list nums
;;

let () =
  let result =
    In_channel.input_lines In_channel.stdin
    |> List.tl_exn
    |> List.map ~f:(String.split ~on:' ')
    |> List.map ~f:(function
      | [ "1"; target ] -> Set.mem single_fibo (Int64.of_string target)
      | [ "2"; target ] -> Set.mem double_fibo (Int64.of_string target)
      | [ "3"; target ] -> Set.mem triple_fibo (Int64.of_string target)
      | _ -> assert false)
    |> List.map ~f:(fun b -> if b then "YES" else "NO")
    |> String.concat_lines
  in
  Out_channel.output_string stdout result
;;
