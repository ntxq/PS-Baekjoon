open! StdLabels
open! MoreLabels

let make_snail n target =
  let snail = Array.make_matrix ~dimx:n ~dimy:n 0 in
  let x = ref 0 in
  let y = ref (-1) in
  let cnt = ref (n * n) in
  let tx = ref (n / 2) in
  let ty = ref (n / 2) in
  let rec draw_line dx dy len =
    if len > 0
    then (
      x := !x + dx;
      y := !y + dy;
      snail.(!y).(!x) <- !cnt;
      if !cnt = target
      then (
        tx := !x;
        ty := !y);
      decr cnt;
      draw_line dx dy (len - 1))
  in
  for i = 1 to n / 2 do
    let len = n - (i * 2) + 1 in
    draw_line 0 1 (len + 1);
    draw_line 1 0 len;
    draw_line 0 (-1) len;
    draw_line (-1) 0 (len - 1)
  done;
  snail.(n / 2).(n / 2) <- 1;
  snail, (!tx, !ty)
;;

let print_snail snail n =
  for i = 0 to n - 1 do
    for j = 0 to n - 1 do
      snail.(i).(j) |> string_of_int |> output_string stdout;
      output_string stdout " "
    done;
    output_string stdout "\n"
  done
;;

let () =
  let n = input_line stdin |> int_of_string in
  let target = input_line stdin |> int_of_string in
  let snail, (tx, ty) = make_snail n target in
  print_snail snail n;
  Printf.sprintf "%d %d\n" (ty + 1) (tx + 1) |> output_string stdout
;;
