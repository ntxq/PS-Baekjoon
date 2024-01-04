open! Core

let knapsack target hay =
  let rec loop hay acc =
    match hay with
    | [] -> acc
    | [ w; c ] :: xs ->
      let next_acc = Array.create ~len:60000 Int.max_value_30_bits in
      for i = 0 to w - 1 do
        next_acc.(i) <- acc.(i)
      done;
      for i = w to 59999 do
        next_acc.(i) <- Int.min acc.(i) (next_acc.(i - w) + c)
      done;
      loop xs next_acc
    | _ -> acc
  in
  let acc = Array.create ~len:60000 Int.max_value_30_bits in
  acc.(0) <- 0;
  loop hay acc
  |> Array.foldi ~init:Int.max_value_30_bits ~f:(fun i acc x ->
    if i < target then acc else Int.min acc x)
;;

let () =
  match In_channel.input_lines In_channel.stdin with
  | params :: hay ->
    let target = String.split params ~on:' ' |> List.last_exn |> Int.of_string in
    let hay =
      List.map hay ~f:(String.split ~on:' ') |> List.map ~f:(List.map ~f:Int.of_string)
    in
    let output = knapsack target hay in
    Out_channel.output_string stdout [%string "%{output#Int}\n"]
  | _ -> ()
;;
