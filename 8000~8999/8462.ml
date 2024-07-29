open! StdLabels
open! MoreLabels

let mos t nums queries =
  let counts = Array.make 1000001 0 in
  let answers = Array.make t 0L in
  let add x =
    let to_sub = Int64.(mul (of_int counts.(x)) (of_int counts.(x)) |> mul (of_int x)) in
    counts.(x) <- counts.(x) + 1;
    let to_add = Int64.(mul (of_int counts.(x)) (of_int counts.(x)) |> mul (of_int x)) in
    Int64.sub to_add to_sub
  in
  let sub x =
    let to_sub = Int64.(mul (of_int counts.(x)) (of_int counts.(x)) |> mul (of_int x)) in
    counts.(x) <- counts.(x) - 1;
    let to_add = Int64.(mul (of_int counts.(x)) (of_int counts.(x)) |> mul (of_int x)) in
    Int64.sub to_add to_sub
  in
  let rec loop cur_l cur_r cur_sum queries =
    match queries with
    | [] -> answers
    | (idx, l, r) :: qs ->
      let sum = ref cur_sum in
      for i = cur_l - 1 downto l do
        sum := Int64.add !sum (add nums.(i))
      done;
      for i = cur_r + 1 to r do
        sum := Int64.add !sum (add nums.(i))
      done;
      for i = cur_l to l - 1 do
        sum := Int64.add !sum (sub nums.(i))
      done;
      for i = cur_r downto r + 1 do
        sum := Int64.add !sum (sub nums.(i))
      done;
      answers.(idx) <- !sum;
      loop l r !sum qs
  in
  loop 0 (-1) 0L queries
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; t ] ->
    let block_size = int_of_float (sqrt (float_of_int n)) in
    let nums =
      input_line stdin
      |> String.split_on_char ~sep:' '
      |> List.map ~f:int_of_string
      |> Array.of_list
    in
    let queries =
      List.init ~len:t ~f:(fun idx ->
        idx
        :: (input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string))
      |> List.map ~f:(function
        | [ idx; l; r ] -> idx, l - 1, r - 1
        | _ -> assert false)
      |> List.fast_sort ~cmp:(fun (_, l1, r1) (_, l2, r2) ->
        if l1 / block_size = l2 / block_size then r1 - r2 else l1 - l2)
    in
    mos t nums queries
    |> Array.iter ~f:(fun ans -> output_string stdout (Int64.to_string ans ^ "\n"))
  | _ -> ()
;;
