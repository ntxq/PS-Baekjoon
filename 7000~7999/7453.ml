(* open! Core *)
open! StdLabels

let () =
  let n = input_line stdin |> int_of_string in
  let a = Bigarray.Array1.create Bigarray.int Bigarray.c_layout n in
  let b = Bigarray.Array1.create Bigarray.int Bigarray.c_layout n in
  let c = Bigarray.Array1.create Bigarray.int Bigarray.c_layout n in
  let d = Bigarray.Array1.create Bigarray.int Bigarray.c_layout n in
  for i = 0 to n - 1 do
    match
      input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
    with
    | [ a_i; b_i; c_i; d_i ] ->
      Bigarray.Array1.unsafe_set a i a_i;
      Bigarray.Array1.unsafe_set b i b_i;
      Bigarray.Array1.unsafe_set c i c_i;
      Bigarray.Array1.unsafe_set d i d_i
    | _ -> assert false
  done;
  let ab = Hashtbl.create (n * n) in
  for i = 0 to n - 1 do
    let a_i = Bigarray.Array1.unsafe_get a i in
    for j = 0 to n - 1 do
      let b_j = Bigarray.Array1.unsafe_get b j in
      let ab_ij = a_i + b_j in
      Hashtbl.add
        ab
        ab_ij
        (Hashtbl.find_opt ab ab_ij
         |> function
         | None -> 1
         | Some x -> x + 1)
    done
  done;
  let cnt = ref 0 in
  for i = 0 to n - 1 do
    let c_i = Bigarray.Array1.unsafe_get c i in
    for j = 0 to n - 1 do
      let d_j = Bigarray.Array1.unsafe_get d j in
      let cd_ij = c_i + d_j in
      cnt
      := !cnt
         + (Hashtbl.find_opt ab (-cd_ij)
            |> function
            | None -> 0
            | Some x -> x)
    done
  done;
  output_string stdout (string_of_int !cnt ^ "\n")
;;
