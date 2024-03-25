(* open! Core *)
open! StdLabels

let rec dfs u adj colors =
  List.iter adj.(u) ~f:(fun v ->
    match colors.(v) with
    | -1 ->
      colors.(v) <- 1 - colors.(u);
      dfs v adj colors
    | _ -> ())
;;

let () =
  let n = input_line stdin |> int_of_string in
  let adj = Array.init n ~f:(fun _ -> []) in
  let ans = ref [] in
  for _ = 1 to n - 1 do
    let u, v =
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ u; v ] -> u, v
      | _ -> assert false
    in
    adj.(u - 1) <- (v - 1) :: adj.(u - 1);
    adj.(v - 1) <- (u - 1) :: adj.(v - 1);
    ans := (u - 1) :: !ans
  done;
  let colors = Array.make n (-1) in
  for u = 0 to n - 1 do
    if colors.(u) = -1
    then (
      colors.(u) <- 0;
      dfs u adj colors)
  done;
  List.rev !ans
  |> List.map ~f:(fun u -> colors.(u))
  |> List.iter ~f:(fun x -> output_string stdout (string_of_int x ^ "\n"))
;;
