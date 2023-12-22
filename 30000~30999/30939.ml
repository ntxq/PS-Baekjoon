open! Core

let snowflake_size i j board =
  let x = Array.length board in
  let y = Array.length board.(0) in
  let rec loop i j dx dy target acc =
    if i < 0 || i >= x || j < 0 || j >= y
    then acc
    else if Char.(board.(i).(j) = target)
    then loop (i + dx) (j + dy) dx dy target (acc + 1)
    else acc
  in
  let dx = [ -1; -1; -1; 0; 1; 1; 1; 0 ] in
  let dy = [ -1; 0; 1; 1; 1; 0; -1; -1 ] in
  let targets = [ '\\'; '|'; '/'; '-'; '\\'; '|'; '/'; '-' ] in
  List.map3_exn dx dy targets ~f:(fun dx dy target ->
    loop (i + dx) (j + dy) dx dy target 0)
  |> List.fold ~init:Int.max_value ~f:min
;;

let find_largest_snowflake board =
  let x = Array.length board in
  let y = Array.length board.(0) in
  let rec loop i j acc =
    if i = x
    then acc
    else if j = y
    then loop (i + 1) 0 acc
    else if Char.(board.(i).(j) = '+')
    then snowflake_size i j board |> max acc |> loop i (j + 1)
    else loop i (j + 1) acc
  in
  loop 0 0 0
;;

let () =
  (match In_channel.input_lines In_channel.stdin with
   | _ :: inputs ->
     let max_size =
       Array.of_list_map inputs ~f:String.to_array |> find_largest_snowflake
     in
     [%string "%{max_size#Int}\n"]
   | [] -> assert false)
  |> Out_channel.output_string stdout
;;
