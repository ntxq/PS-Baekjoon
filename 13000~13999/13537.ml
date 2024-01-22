(* open! Core *)
open! StdLabels

let tree = Array.init (4 * 100000) ~f:(fun _ -> Array.make 0 0)

let merge l r =
  let merged = Array.make (Array.length l + Array.length r) 0 in
  let rec loop i j k =
    if i = Array.length l
    then (
      Array.blit ~src:r ~src_pos:j ~dst:merged ~dst_pos:k ~len:(Array.length r - j);
      merged)
    else if j = Array.length r
    then (
      Array.blit ~src:l ~src_pos:i ~dst:merged ~dst_pos:k ~len:(Array.length l - i);
      merged)
    else if l.(i) <= r.(j)
    then (
      merged.(k) <- l.(i);
      loop (i + 1) j (k + 1))
    else (
      merged.(k) <- r.(j);
      loop i (j + 1) (k + 1))
  in
  loop 0 0 0
;;

let rec build input v tl tr =
  if tl = tr
  then tree.(v) <- Array.make 1 input.(tl)
  else (
    let tm = (tl + tr) / 2 in
    build input (2 * v) tl tm;
    build input ((2 * v) + 1) (tm + 1) tr;
    tree.(v) <- merge tree.(2 * v) tree.((2 * v) + 1))
;;

let upper_bound arr x =
  let rec loop l r =
    if l >= r
    then l
    else (
      let m = (l + r) / 2 in
      if arr.(m) <= x then loop (m + 1) r else loop l m)
  in
  loop 0 (Array.length arr)
;;

let count arr x =
  let ub = upper_bound arr x in
  Array.length arr - ub
;;

let rec query v tl tr l r x =
  if l > r
  then 0
  else if l = tl && r = tr
  then count tree.(v) x
  else (
    let tm = (tl + tr) / 2 in
    query (2 * v) tl tm l (min r tm) x
    + query ((2 * v) + 1) (tm + 1) tr (max l (tm + 1)) r x)
;;

let () =
  let n = input_line stdin |> int_of_string in
  let input =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string
    |> Array.of_list
  in
  build input 1 0 (n - 1);
  let m = input_line stdin |> int_of_string in
  for _ = 1 to m do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ l; r; x ] ->
      let ans = query 1 0 (n - 1) (l - 1) (r - 1) x |> string_of_int in
      output_string stdout (ans ^ "\n")
    | _ -> assert false
  done
;;
