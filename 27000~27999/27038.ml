(* open! Core *)
open! StdLabels

let knapsack n s =
  let dp = Bigarray.Array2.create Bigarray.int Bigarray.c_layout (n + 1) s in
  Bigarray.Array2.fill dp 0;
  Bigarray.Array2.set dp 0 0 1;
  let m = float_of_int s |> sqrt |> int_of_float in
  for i = 1 to m do
    let w = i * i in
    for j = n downto 1 do
      for k = s - 1 downto w do
        Bigarray.Array2.set
          dp
          j
          k
          (Bigarray.Array2.get dp (j - 1) (k - w) + Bigarray.Array2.get dp j k)
      done
    done
  done;
  List.init ~len:s ~f:(fun i -> Bigarray.Array2.get dp n i)
  |> List.fold_left ~init:0L ~f:(fun acc x -> Int64.add acc (Int64.of_int x))
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ n; s ] ->
    let res = knapsack n s |> Int64.to_string in
    output_string stdout (res ^ "\n")
  | _ -> ()
;;
