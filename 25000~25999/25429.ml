(* open! Core *)
open! StdLabels
open! MoreLabels
module LongMap = Map.Make (Int64)

let print_result total conflicts =
  if Int64.equal conflicts 0L
  then output_string stdout ("YES " ^ Int64.to_string total ^ "\n")
  else output_string stdout "NO\n"
;;

let rec handle_query l slices groups total conflicts =
  match input_line stdin with
  | exception End_of_file -> ()
  | line ->
    (match String.split_on_char line ~sep:' ' |> List.map ~f:Int64.of_string with
     | [ 1L; x; t ] ->
       let x = Int64.sub x 1L in
       let prev_val = LongMap.find_opt x slices |> Option.value ~default:0L in
       let total = Int64.sub total prev_val |> Int64.add t in
       let slices = LongMap.add slices ~key:x ~data:t in
       let groups =
         if Int64.equal prev_val 0L
         then
           LongMap.update groups ~key:(Int64.rem x l) ~f:(function
             | None -> Some 1L
             | Some v -> Some (Int64.add v 1L))
         else groups
       in
       let conflicts =
         if Int64.equal prev_val 0L
            && LongMap.find (Int64.rem x l) groups |> Int64.equal 2L
         then Int64.add conflicts 1L
         else conflicts
       in
       print_result total conflicts;
       handle_query l slices groups total conflicts
     | [ 2L; x ] ->
       let x = Int64.sub x 1L in
       let prev_val = LongMap.find x slices in
       let total = Int64.sub total prev_val in
       let slices = LongMap.remove x slices in
       let groups =
         LongMap.update groups ~key:(Int64.rem x l) ~f:(function
           | None -> None
           | Some v -> Some (Int64.sub v 1L))
       in
       let conflicts =
         if LongMap.find (Int64.rem x l) groups |> Int64.equal 1L
         then Int64.sub conflicts 1L
         else conflicts
       in
       print_result total conflicts;
       handle_query l slices groups total conflicts
     | _ -> ())
;;

let () =
  match
    input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:Int64.of_string
  with
  | [ _; l; _ ] -> handle_query l LongMap.empty LongMap.empty 0L 0L
  | _ -> assert false
;;
