(* open! Core *)
open! StdLabels
open! MoreLabels

let build_coast knapsack components =
  knapsack.(0).(0) <- 0;
  for i = 0 to Array.length knapsack - 1 do
    for j = 0 to Array.length knapsack.(i) - 1 do
      let cur_fun = knapsack.(i).(j) in
      List.iter components.(i) ~f:(fun (w, f, c) ->
        let nw = i + w in
        let nc = j + c in
        let nf = cur_fun + f in
        if nw < Array.length knapsack
           && nc < Array.length knapsack.(nw)
           && nf > knapsack.(nw).(nc)
        then knapsack.(nw).(nc) <- nf)
    done
  done;
  Array.fold_left knapsack.(Array.length knapsack - 1) ~init:(-1) ~f:max
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
  with
  | [ l; n; b ] ->
    let knapsack = Array.make_matrix ~dimx:(l + 1) ~dimy:(b + 1) min_int in
    let components = Array.init (l + 1) ~f:(fun _ -> []) in
    for _ = 0 to n - 1 do
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ x; w; f; c ] -> components.(x) <- (w, f, c) :: components.(x)
      | _ -> assert false
    done;
    build_coast knapsack components |> string_of_int |> output_string stdout;
    output_char stdout '\n'
  | _ -> assert false
;;
