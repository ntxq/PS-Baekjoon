open! StdLabels
open! MoreLabels

let () =
  let lines = Array.make_matrix ~dimx:101 ~dimy:101 0 in
  for _ = 1 to input_line stdin |> int_of_string do
    Scanf.scanf "%d %d\n" (fun u v ->
      lines.(u).(v) <- 1;
      lines.(v).(u) <- 1)
  done;
  let dp = Array.make_matrix ~dimx:101 ~dimy:101 0 in
  for i = 1 to 100 do
    for j = i downto 1 do
      for k = j to (i - 1) do
        dp.(j).(i) <- max dp.(j).(i) (dp.(j).(k) + dp.(k).(i) + lines.(i).(j))
      done
    done
  done;
  Printf.printf "%d\n" dp.(1).(100)
;;
