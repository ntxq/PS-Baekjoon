(* open! Core *)
open! StdLabels
open! MoreLabels

let find_two_squares n points =
  Array.fast_sort points ~cmp:(fun (x1, y1) (x2, y2) ->
    if x1 = x2 then y1 - y2 else x1 - x2);
  let minYLtoR = Array.make n 0 in
  let maxYLtoR = Array.make n 0 in
  minYLtoR.(0) <- snd points.(0);
  maxYLtoR.(0) <- snd points.(0);
  for i = 1 to n - 1 do
    minYLtoR.(i) <- min minYLtoR.(i - 1) (snd points.(i));
    maxYLtoR.(i) <- max maxYLtoR.(i - 1) (snd points.(i))
  done;
  let minYRtoL = Array.make n 0 in
  let maxYRtoL = Array.make n 0 in
  minYRtoL.(n - 1) <- snd points.(n - 1);
  maxYRtoL.(n - 1) <- snd points.(n - 1);
  for i = n - 2 downto 0 do
    minYRtoL.(i) <- min minYRtoL.(i + 1) (snd points.(i));
    maxYRtoL.(i) <- max maxYRtoL.(i + 1) (snd points.(i))
  done;
  let sx = fst points.(0) in
  let tx = fst points.(n - 1) in
  let rec loop idx acc =
    if idx = n
    then acc
    else
      let open Int64 in
      let lx = fst points.(idx - 1) in
      let lminY = minYLtoR.(idx - 1) in
      let lmaxY = maxYLtoR.(idx - 1) in
      let lArea = mul (of_int (lmaxY - lminY)) (of_int (lx - sx)) in
      let rx = fst points.(idx) in
      let rminY = minYRtoL.(idx) in
      let rmaxY = maxYRtoL.(idx) in
      let rArea = mul (of_int (rmaxY - rminY)) (of_int (tx - rx)) in
      loop (idx + 1) (min acc (max lArea rArea))
  in
  loop 1 Int64.max_int
;;

let () =
  let t = input_line stdin |> int_of_string in
  for _ = 1 to t do
    let n = input_line stdin |> int_of_string in
    let points = Array.make n (0, 0) in
    for i = 0 to n - 1 do
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ x; y ] -> points.(i) <- x, y
      | _ -> assert false
    done;
    (if n = 1
     then 0L
     else
       min
         (find_two_squares n points)
         (Array.map points ~f:(fun (x, y) -> y, x) |> find_two_squares n))
    |> Int64.to_string
    |> output_string stdout;
    output_char stdout '\n'
  done
;;
