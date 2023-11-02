open! StdLabels
open! MoreLabels

type t =
  | First
  | Last
  | Normal

let query arr =
  let module IntSet = Set.Make (Int) in
  let ranges = Array.make (Array.length arr + 1) (Array.length arr + 1, -1) in
  for i = 0 to Array.length arr - 1 do
    let x = arr.(i) in
    let l, r = ranges.(x) in
    ranges.(x) <- min l i, max r i
  done;
  let types = Array.make (Array.length arr) Normal in
  Array.iter ranges ~f:(fun (l, r) ->
    if r != -1 && l != r
    then (
      types.(l) <- First;
      types.(r) <- Last));
  let s = ref IntSet.empty in
  let is_strange = ref true in
  for i = 0 to Array.length arr - 1 do
    (match types.(i) with
     | First -> s := IntSet.add arr.(i) !s
     | Last -> s := IntSet.remove arr.(i) !s
     | Normal -> ());
    is_strange
      := !is_strange
         && IntSet.min_elt_opt !s |> Option.fold ~none:true ~some:(fun x -> arr.(i) <= x)
  done;
  if !is_strange then "Yes\n" else "No\n"
;;

let () =
  let t = input_line stdin |> int_of_string in
  for _ = 1 to t do
    let _ = input_line stdin in
    let arr =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> Array.of_list
    in
    query arr |> output_string stdout
  done
;;
